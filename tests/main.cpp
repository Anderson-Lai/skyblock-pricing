#include "api.h"
#include <iostream>

int main(int argc, char** argv)
{
    std::setlocale(LC_ALL, "en_US.utf8");
    curl_global_init(CURL_GLOBAL_DEFAULT);

    Api caller("https://api.hypixel.net/v2/skyblock/auctions?page=0");
    std::cout << caller.Call() << "\n";

    curl_global_cleanup();
    return 0;
}
