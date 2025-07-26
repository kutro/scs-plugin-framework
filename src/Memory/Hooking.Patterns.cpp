#include "SPF/Memory/Hooking.hpp"

#include <Psapi.h>

SPF_NS_BEGIN

uintptr_t GetBaseAddress()
{
    return reinterpret_cast<uintptr_t>(GetModuleHandle(nullptr));
}

std::vector<uintptr_t> FindPattern(const char* pattern, const char* mask)
{
    std::vector<uintptr_t> result;

    uintptr_t baseAddress = GetBaseAddress();

    MODULEINFO moduleInfo;
    GetModuleInformation(GetCurrentProcess(), reinterpret_cast<HMODULE>(baseAddress), &moduleInfo, sizeof(MODULEINFO));

    uintptr_t endAddress = baseAddress + moduleInfo.SizeOfImage;

    size_t patternLength = strlen(mask);

    for (uintptr_t i = baseAddress; i < endAddress - patternLength; ++i)
    {
        bool found = true;
        for (size_t j = 0; j < patternLength; ++j)
        {
            if (mask[j] != '?' && pattern[j] != reinterpret_cast<char*>(i)[j])
            {
                found = false;
                break;
            }
        }

        if (found)
        {
            result.push_back(i);
        }
    }

    return result;
}

SPF_NS_END
