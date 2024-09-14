#include "auctionhouse.h"

long long AuctionHouse::LookupPrice(const std::wstring& itemName) const
{
    if (m_prices.find(itemName) != m_prices.end())
    {
        return m_prices.at(itemName);
    }
    return INT64_MIN;
}

void AuctionHouse::ScrapeAuction()
{

}

void AuctionHouse::ReadFileData(const std::string& fileName)
{

}

const std::unordered_map<std::wstring, long long>& AuctionHouse::GetPrices() const
{
    return m_prices;
}
