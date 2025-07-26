#pragma once

#include <cstdint>
#include <vector>

#include <windows.h>

#include "Namespace.hpp"

SPF_NS_BEGIN

uintptr_t GetBaseAddress();

std::vector<uintptr_t> FindPattern(const char* pattern, const char* mask);

SPF_NS_END
