#include "auctionhouse.h"
#include "api.h"
#include "conversions.h"
#include "file.h"
#include "json.h"
#include "log.h"
#include <format>
#include <future>
#include "parsing.h"

long long AuctionHouse::LookupPrice(const std::wstring& itemName) const
{
    if (m_lbins.find(itemName) != m_lbins.end())
    {
        return m_lbins.at(itemName);
    }
    return INT64_MIN;
}

void AuctionHouse::ScrapeAuction()
{
    try 
    {
        // start from page 1 
        Api first("https://api.hypixel.net/v2/skyblock/auctions?page=1");
        Json firstResult(first.Call());

        simdjson::ondemand::object& firstObject = firstResult.GetObject();
        const long long pages = firstObject["totalPages"].get_int64();
        simdjson::ondemand::array auctions = firstObject["auctions"].get_array();

        std::vector<std::future<void>> calls(pages);
        this->m_auctionData.clear();
        
        calls.emplace_back(std::async(std::launch::async, [this, &auctions]()
                {
                    this->WriteAuctionPageData(auctions);
                }));

        for (int i = 2; i < pages; i++)
        {
            calls.emplace_back(std::async(std::launch::async, [this, i]()
                        {
                            Api call(std::format("https://api.hypixel.net/v2/skyblock/auctions?page={}", i).c_str());

                            Json result(call.Call());

                            simdjson::ondemand::object& obj = result.GetObject();
                            simdjson::ondemand::array auctions = obj["auctions"].get_array();
                            this->WriteAuctionPageData(auctions);
                        }));
        }

        for (auto& future : calls)
        {
            try 
            {
                future.get();
            }
            catch (const simdjson::simdjson_error& e) 
            {
                Log::Error(std::format("An error occurred while scraping the auction house: {}", e.what()));
            }
        }

        this->ComputeAuctionData();
    }
    catch (...)
    {
        Log::Error("An error occurred while scraping the entire auction house for data");
    }
}

void AuctionHouse::ReadFileData(const std::string& fileName)
{
    try
    {
        std::string contents = File::ReadFile(fileName);
        Json json(contents);
        simdjson::ondemand::object& object = json.GetObject();

        for (auto field : object)
        {
            try 
            {   
                std::string key(static_cast<std::string_view>(field.unescaped_key()));
                this->m_lbins[Conversions::ToWideString(key)] = field.value().get_int64();
            }
            catch (...)
            {
                Log::Error(std::format("An error occurred while reading the contents of {} to seed in past data", fileName));
            }
        }
    }
    catch (const simdjson::simdjson_error& e)
    {
        Log::Error(std::format("An error occurred while reading the JSON contents of {}: {}", fileName, e.what()));
    }
}

const std::unordered_map<std::wstring, long long>& AuctionHouse::GetLbins() const
{
    return m_lbins;
}

void AuctionHouse::ComputeAuctionData()
{
    std::unique_lock<std::shared_mutex> lock(this->m_mutex);
    const int pricesToAverage = 5;
    const double tolerancePercentage = 0.20;

    for (auto& [name, pricesQueue] : this->m_auctionData)
    {
        if (pricesQueue.size() < 15)
        {
            continue; // too little items -> could be being manipulated
        }

        pricesQueue.pop(); // remove the cheapest item, could skew data if it is a flip 
        const unsigned long long secondLowest = pricesQueue.top();
        unsigned long long sum = 0;

        for (int i = 0; i < pricesToAverage && !pricesQueue.empty(); i++)
        {
            sum += pricesQueue.top();
            pricesQueue.pop();
        }

        const unsigned long long average = sum / pricesToAverage;
        
        // calculate the percentage difference between the second lowest bin and the computed average
        const double percentageDifference = (average - secondLowest) / static_cast<double>(secondLowest);

        // if the second lowest is not too cheap (> 83% of the average lbin price), set the newLbin to the second lowest price
        const unsigned long long computedLbin = percentageDifference <= tolerancePercentage ? secondLowest : average; 

        if (this->m_lbins.find(name) == this->m_lbins.end())
        {
            this->m_lbins[name] = computedLbin;
        }
        else 
        {
            const long long previousPrice = this->LookupPrice(name);
            if (computedLbin > static_cast<unsigned long long>(previousPrice))
            {
                this->m_lbins[name] = computedLbin;
            }
            else
            {
                // last chance to clean data 
                const double percentDifference = (previousPrice - computedLbin) / static_cast<double>(computedLbin);

                // if the percentage difference is too high, average the previous and computed prices
                this->m_lbins[name] = percentDifference <= tolerancePercentage 
                    ? computedLbin : (computedLbin + previousPrice) / 2;
            }
        }
    }
}

void AuctionHouse::WriteAuctionPageData(simdjson::ondemand::array& auctions)
{
    std::vector<std::unique_ptr<Item>> bins = Parsing::RemoveAuctions(auctions);
    Parsing::CalculateProfit(std::move(bins), *this); 

    std::unique_lock<std::shared_mutex> lock(this->m_mutex);
    for (const auto& bin : bins)
    {
        this->m_auctionData[bin->GetName()].emplace(bin->GetPrice());
    }
}
