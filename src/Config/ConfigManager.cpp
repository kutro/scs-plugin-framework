#include "SPF/Config/ConfigManager.hpp"
#include "SPF/Config/Config.hpp"

SPF_NS_BEGIN

ConfigManager::ConfigManager() = default;

ConfigManager::~ConfigManager() = default;

Config& ConfigManager::createConfig(const std::string& name)
{
    auto config = std::make_unique<Config>(name);
    auto& configRef = *config;
    _configs.push_back(std::move(config));
    return configRef;
}

SPF_NS_END
