#include "SPF/Config/Config.hpp"
#include "SPF/Config/ConfigFieldBase.hpp"

SPF_NS_BEGIN

Config::Config(std::string name) : _name(std::move(name))
{
}

Config::~Config() = default;

void Config::add(std::unique_ptr<ConfigFieldBase> field)
{
    _fields.push_back(std::move(field));
}

// Other methods will be implemented later...

SPF_NS_END
