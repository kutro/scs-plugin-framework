#include "SPF/Utils/Paths.hpp"

#include <filesystem>

SPF_NS_BEGIN

namespace Paths
{
    std::string ModulePath;
    std::string HomePath;

    void Init(const std::string& modulePath)
    {
        ModulePath = modulePath;

        // Assuming the home path is one level up from the module's directory.
        // e.g., if module is at "C:/Games/ATS/bin/win_x64/plugins/my_plugin.dll",
        // home path will be "C:/Games/ATS/bin/win_x64/".
        HomePath = std::filesystem::path(modulePath).parent_path().parent_path().string();
    }
}

SPF_NS_END
