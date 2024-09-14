#include "auctionhouse.h"
#include "conversions.h"
#include "file.h"
#include "json.h"
#include "log.h"
#include <format>

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
