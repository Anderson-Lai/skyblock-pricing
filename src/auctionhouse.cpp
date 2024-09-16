#include "auctionhouse.h"
#include "api.h"
#include "conversions.h"
#include "file.h"
#include "json.h"
#include "log.h"
#include <format>
#include <future>

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
            Api call(std::format("https://api.hypixel.net/v2/skyblock/auctions?page={}", i).c_str());
            Json result(call.Call());

            simdjson::ondemand::object& obj = result.GetObject();
            simdjson::ondemand::array auctions = obj["auctions"].get_array();
            calls.emplace_back(std::async(std::launch::async, [this, &auctions]()
                        {
                            this->WriteAuctionPageData(auctions);
                        }));
        }

        for (auto& future : calls)
        {
            try 
            {
                future.get();
            }
            catch (...)
            {
                Log::Error("An error occurred while scraping the auction house");
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

const std::unordered_map<std::wstring, long long>& AuctionHouse::GetLbins() const
{
    return m_lbins;
}

void AuctionHouse::ComputeAuctionData()
{
    
}

void AuctionHouse::WriteAuctionPageData(simdjson::ondemand::array& auctions)
{

}
