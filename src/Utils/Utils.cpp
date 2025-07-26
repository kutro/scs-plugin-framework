#include "SPF/Utils/Utils.hpp"

#include <fmt/core.h>
#include <windows.h>
#include <vector>

SPF_NS_BEGIN

namespace Utils
{
    std::string GetModulePath(HMODULE hModule)
    {
        std::vector<char> path(MAX_PATH);
        while (GetModuleFileNameA(hModule, path.data(), path.size()) == path.size())
        {
            path.resize(path.size() * 2);
        }
        return std::string(path.data());
    }

    std::string FormatGUID(const GUID& guid)
    {
        return fmt::format(
            "{{{:08x}-{:04x}-{:04x}-{:02x}{:02x}-{:02x}{:02x}{:02x}{:02x}{:02x}{:02x}}}",
            guid.Data1, guid.Data2, guid.Data3, guid.Data4[0], guid.Data4[1], guid.Data4[2],
            guid.Data4[3], guid.Data4[4], guid.Data4[5], guid.Data4[6], guid.Data4[7]);
    }
}

SPF_NS_END
