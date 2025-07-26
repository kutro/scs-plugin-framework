#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Namespace.hpp"

SPF_NS_BEGIN

class Config; // Forward declaration

class ConfigManager
{
private:
    std::vector<std::unique_ptr<Config>> _configs;

public:
    ConfigManager();
    ~ConfigManager();

    Config& createConfig(const std::string& name);
};

SPF_NS_END
