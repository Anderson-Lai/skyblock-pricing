#pragma once
#include "auctionhouse.h"
#include <string>

namespace File
{
    int CreateFile(const std::string& fileName);
    std::string ReadFile(const std::string& fileName);
    void WritePrices(const std::string& fileName, const AuctionHouse& auctionHouse);
}
