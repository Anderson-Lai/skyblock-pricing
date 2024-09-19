## Linking against the library

This library has been configured to be linked statically. To link dynamically, go to the CMakeLists.txt and change the add\_library() type from STATIC to SHARED.  

Linking with CMake:  
``` cmake
FetchContent_Declare(
    skyblock_pricing 
    GIT_REPOSITORY https://github.com/Anderson-Lai/skyblock-pricing.git
    GIT_TAG master
)
FetchContent_MakeAvailable(skyblock_pricing)

target_link_libraries(${PROJECT_NAME}
    PRIVATE
        skyblock_pricing
)
```

## Using the library

This library exposes 3 main header files you can use: pricinglibrary.h, timing.h, conversions.h, and in a sense, item.h, although you should never #include it unless you
absolutely understand what you are doing (auctionhouse.h should almost never be #include 'd, as its API can be used through other, much easier-to-use APIs found in this library).

### pricinglibrary.h

``` cpp
namespace PricingLibrary
{
    int Initialize();
    long long GetPrice(const std::string& itemName);
    long long GetPrice(const std::wstring& itemName);
    std::vector<std::unique_ptr<Item>> GetFlips();
    void CleanUp();
}
```

In your program's initialization, call PricingLibrary::Initialize() - it sets up all that is needed for the library to work properly. If initialization fails, it will
return a non-zero exit code. It is highly recommended to immediately terminate your program if Initialization returns a non-zero exit code.  

In your program's cleanup, call PricingLibrary::CleanUp() - it frees all memory and resources allocated by the library during its usage.  

PricingLibrary::GetPrice(const std::wstring& itemName) and PricingLibrary::GetPrice(const std::string& itemName) provides a simple API for you to lookup the average lowest bin of an item.  

PricingLibrary::GetFlips() calls the Hypixel API to get the most recent auctions, and calls PricingLibrary::GetPrice() on all bins. It returns all profitable flips over 1,000,000
coins sorted from least to most profitable.

### timing.h

``` cpp
namespace Timing
{
    std::chrono::time_point<std::chrono::high_resolution_clock> Now();
    void Sleep(const unsigned long long milliseconds);
    unsigned long long SecondsSinceEpoch();
    void Log(const std::chrono::time_point<std::chrono::high_resolution_clock>& begin,
            const std::chrono::time_point<std::chrono::high_resolution_clock>& end);
    unsigned long long CurrentSecondInMinute();
}
```

Timing::Now() returns the current time relative to an ARBITRARY point in time, thus, it should only be used in timing execution speed.  

Timing::Sleep(unsigned long long milliseconds) sleeps the calling thread for the specified number of milliseconds.  

Timing::SecondsSinceEpoch() returns the seconds since the epoch, a fixed, non-arbitrary point in time. Thus, unlike Timing::Now(), it can be used to get the current time. However, 
it can also be used to time execution speed.  

Timing::Log(const std::chrono::time\_point\<std::chrono::high\_resolution\_clok>& begin, const std::chrono::time\_point\<std::chrono::high\_resolution\_clok>& end) provides a simple
way to log the return values of Timing::Now(). It will calculate the time difference between those two points in milliseconds, and output it to stdout.  

Timing::CurrentSecondInMinute() returns the current second in the minute, thus, its values will be between [0-59]. It can be combined with PricingLibrary::GetFlips() to get new flips
as soon as they appear, which is the start of every minute (when Timing::CurrentSecondInMinute == 0), which is when the Hypixel API updates every minute.  

### conversions.h

``` cpp
namespace Conversions
{
    std::wstring ToWideString(const char* str);
    std::wstring ToWideString(const std::string& str);
    std::string ToNarrowString(const std::wstring& str);
}
```

Conversions::ToWideString(const char* str) and Conversions::ToWideString(const std::string& str) takes in a UTF-8 encoded string and returns a deep-copied, UTF-16 or a UTF-32 encoded
representation of the string, std::wstring (the differene in encoding varies between operating systems and implementations, Windows' std::wstring is normally UTF-16,
whereas Linux's and MacOs' are normaly UTF-32).  

Conversions::ToNarrowString(const std::wstring& str) takes in a UTF-16 or UTF-32 encoded string (read above to understand why std::wstring may have different encodings), and returns
a deep-copied, UTF-8 representation of the string, std::string.

### item.h

``` cpp
class Item
{
public:
    Item(const std::string_view uuid, const std::string_view rarity, const std::string_view category,
            const std::string_view itemName, const std::string_view itemLore, const long long price,
            const long long startTime);
    void CalculateProfit(const AuctionHouse& auctionHouse);
    const std::wstring& GetName() const;
    long long GetPrice() const;
    long long GetProfit() const;
    const std::string& GetUuid() const;
    long long GetStartTime() const;
private:
    ...
};
```

Item::CalculateProfit(const AuctionHouse& auctionHouse) should never be called, as the library manages its own internal AuctionHouse instance.  

The constructor should also never be called, as there is no good reason to construct an Item object without being able to calculate its profit or being able to view it on the
in-game auction house without an auction uuid.

The remaining public functions are getters for the item's internal member variables. Item::GetName() retuns a const reference to the item's name as a std::wstring.
Item::GetPrice() returns the item's price as a long long. Item::GetProfit() returns the item's profit as a long long. Item::GetUuid() returns a const reference to the
auction uuid of this item as a std::string. This can be used to view the auction on the in-game auction house with /viewauction [uuid]. Item::GetStartTime() returns the time
at which the auciton was put up on the in-game auction house, in seconds since the epoch.

### auctionhouse.h

Do not include this file, as the library manages its own internal AuctionHouse instance which is used to provide simpler APIs to use in place of the AuctionHouse class' API. If 
you insist on using this header file, read the source code for the [header file](https://github.com/Anderson-Lai/skyblock-pricing/blob/master/include/public/auctionhouse.h)
and the source code for the [implementation file](https://github.com/Anderson-Lai/skyblock-pricing/blob/master/src/auctionhouse.cpp) to understand its API.
This header file is left intentionally undocumented to deter its direct use.
