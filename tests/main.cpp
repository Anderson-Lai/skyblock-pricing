#include "curl/curl.h"

int main(int argc, char** argv) {
    curl_global_init(CURL_GLOBAL_DEFAULT);
    CURL* curl = curl_easy_init();
    auto res = curl_easy_setopt(curl, CURLOPT_URL, "https://dummyjson.com/products");
    if (res != CURLE_OK) {
        fprintf(stderr, "something went wrong");
        return 1;
    }

    return 0;
}
