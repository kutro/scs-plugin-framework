#pragma once

#include <string>

#include "Namespace.hpp"

SPF_NS_BEGIN

namespace Paths
{
    // Path to the module's DLL
    extern std::string ModulePath;

    // Path to the framework's home directory (for configs, logs, etc.)
    extern std::string HomePath;

    // Initializes the paths. Must be called once at startup.
    void Init(const std::string& modulePath);
}

SPF_NS_END
