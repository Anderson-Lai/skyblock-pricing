#pragma once
#include <shared_mutex>
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include "simdjson.h"

class AuctionHouse
{
public:
    long long LookupPrice(const std::wstring& itemName) const;
    void ScrapeAuction();
    void ReadFileData(const std::string& fileName);
    const std::unordered_map<std::wstring, long long>& GetLbins() const;
private:
    void ComputeAuctionData();
    void WriteAuctionPageData(simdjson::ondemand::array& auctions);
private:
    // contains the data on the entire auction house
    std::unordered_map<std::wstring, 
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>>> m_auctionData;
    // contains only the lbins of items
    std::unordered_map<std::wstring, long long> m_lbins;
    std::shared_mutex m_mutex;
};
