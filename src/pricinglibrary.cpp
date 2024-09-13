#include "pricinglibrary.h"
#include "curl/curl.h"
#include <clocale>

void PricingLibrary::Initialize()
{
    curl_global_init(CURL_GLOBAL_DEFAULT); 
    std::setlocale(LC_ALL, "en_US.utf8");
}

void PricingLibrary::CleanUp()
{
    curl_global_cleanup();
}
