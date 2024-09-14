#include "cleaning.h"
#include <array>
#include <algorithm>

namespace Cleaning
{
    inline const std::array<wchar_t, 68> importantCharacters = { L'0', L'1', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9',
    L'a', L'b', L'c', L'd', L'e', L'f', L'g', L'h', L'i', L'j', L'k', L'l', L'm', L'n', L'o', L'p', L'q', L'r', L's', L't', L'u', L'v',
    L'w', L'x', L'y', L'z', L'A', L'B', L'C', L'D', L'E', L'F', L'G', L'H', L'I', L'J', L'K', L'L', L'M', L'N', L'O', L'P' , L'Q',
    L'R', L'S', L'T', L'U', L'V', L'W', L'X', L'Y', L'Z', L'-', L'\'', L'™', L'©', L',', L'⚚' };

    inline const std::array<std::wstring, 10> duplicateReforges = {
        L"Very", L"Highly", L"Extremely", L"Not", L"So", L"Thicc",
        L"Absolutely", L"Even", L"More", L"Greater"
    };

    inline const std::array<std::wstring, 114> reforges = {
        // sword reforges (19 total)
        L"Epic", L"Fair", L"Fast", L"Gentle", L"Heroic", L"Legendary", L"Odd", L"Sharp", L"Spicy", L"Coldfused",
        L"Dirty", L"Fabled", L"Gilded", L"Suspicious", L"Warped", L"Withered", L"Bulky", L"Jerry's", L"Fanged",

        // bow reforges (12 total)
        L"Awkward", L"Deadly", L"Fine", L"Grand", L"Hasty", L"Neat", L"Rapid", L"Rich", L"Unreal", L"Precise",
        L"Spiritual", L"Headstrong",

        // armour reforges (28 total)
        L"Clean", L"Fierce", L"Heavy", L"Light", L"Mythic", L"Pure", L"Titanic", L"Smart", L"Wise", L"Candied",
        L"Submerged", L"Perfect", L"Reinforced", L"Renowned", L"Spiked", L"Hyper", L"Giant", L"Jaded", L"Cubic", L"Necrotic",
        L"Empowered", L"Ancient", L"Undead", L"Loving", L"Ridiculous", L"Bustling", L"Mossy", L"Festive", 

        // equipment reforges (17 total)
        L"Stained", L"Menacing", L"Hefty", L"Soft", L"Honored", L"Blended", L"Astute", L"Colossal", L"Brilliant", L"Glistening",
        L"Strengthened", L"Waxed", L"Fortified", L"Rooted", L"Blooming", L"Snowy", L"Blood-Soaked",

        // fishing rod reforges (7 total)
        L"Salty", L"Treacherous", L"Lucky", L"Stiff", L"Dirty", L"Chomp", L"Pitchin'",

        // pickaxe reforges (14 total)
        L"Unyielding", L"Prospector's", L"Excellent", L"Sturdy", L"Fortunate", L"Ambered", L"Auspicious", L"Fleet", L"Heated", L"Magnetic",
        L"Mithraic", L"Refined", L"Stellar", L"Fruitful",

        // axe reforges (9 total)
        L"Great", L"Rugged", L"Lush", L"Lumberjack's", L"Double-Bit", L"Moil", L"Toil", L"Blessed", L"Earthy",

        // hoe reforges (6 total)
        L"Robust", L"Zooming", L"Peasant's", L"Green Thumb", L"Blessed", L"Bountiful", 

        // vacuum reforges (2 total) (what is a vacuum???)
        L"Beady", L"Buzzing",
    };
}

bool Cleaning::IsImportantCharacter(const wchar_t character)
{
    if (std::find(importantCharacters.begin(), importantCharacters.end(), character) != importantCharacters.end())
    {
        return true;
    }
    return false;
}

bool Cleaning::IsDuplicateReforge(const std::wstring& word)
{
    if (std::find(duplicateReforges.begin(), duplicateReforges.end(), word) != duplicateReforges.end())
    {
        return true;
    }
    return false;
}

bool Cleaning::IsReforge(const std::wstring& word)
{
    if (std::find(reforges.begin(), reforges.end(), word) != reforges.end())
    {
        return true;
    }
    return false;
}

bool Cleaning::IsRecombobulated(const std::wstring& itemLore)
{
    return itemLore.find(L"§ka") != std::string::npos;
}
