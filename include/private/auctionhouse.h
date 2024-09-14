#pragma once
#include <string>
#include <unordered_map>
#include <vector>
#include <queue>
#include <mutex>

class AuctionHouse
{
    long long LookupPrice(const std::wstring& itemName) const;
    void ScrapeAuction();
    void ReadFileData(const std::string& fileName);
private:
    std::unordered_map<std::wstring, 
        std::priority_queue<long long, std::vector<long long>, std::greater<long long>>> m_averages;
    std::unordered_map<std::wstring, long long> m_prices;
    std::mutex m_mutex;
};
