#include "SPF/KeyBinding/KeyBinds.hpp"

#include <utility>

SPF_NS_BEGIN

KeyBinds::KeyBinds(std::string name) : _name(std::move(name))
{
}

KeyBinds::~KeyBinds() = default;

// Other methods will be implemented later...

SPF_NS_END
