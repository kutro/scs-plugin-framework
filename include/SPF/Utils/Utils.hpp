#pragma once

#include <string>
#include <windows.h> // For GUID and HMODULE/HINSTANCE

#include "Namespace.hpp"

SPF_NS_BEGIN

namespace Utils
{
    std::string GetModulePath(HMODULE hModule);
    std::string FormatGUID(const GUID& guid);
}

SPF_NS_END
