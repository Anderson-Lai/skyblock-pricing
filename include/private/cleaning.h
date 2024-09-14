#pragma once
#include <string>

namespace Cleaning  
{
    bool IsImportantCharacter(const wchar_t character);
    bool IsDuplicateReforge(const std::wstring& word);
    bool IsReforge(const std::wstring& word);
    bool IsRecombobulated(const std::wstring& itemLore);
}
