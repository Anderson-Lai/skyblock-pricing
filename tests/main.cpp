#include "api.h"
#include <iostream>
#include "pricinglibrary.h"

int main(int argc, char** argv)
{
    PricingLibrary::Initialize();

    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    std::cout << caller.Call() << "\n";
    
    PricingLibrary::CleanUp();
    return 0;
}
