#include "SPF/KeyBinding/KeyBindsManager.hpp"

SPF_NS_BEGIN

KeyBindsManager::KeyBindsManager(EventDispatcher& eventDispatcher)
    : _eventDispatcher(eventDispatcher)
{
}

KeyBinds& KeyBindsManager::createKeyBinds(const std::string& name)
{
    auto keyBinds = std::make_unique<KeyBinds>(name);
    auto& ref = *keyBinds;
    _keyBinds.push_back(std::move(keyBinds));
    return ref;
}

// Other methods will be implemented later...

SPF_NS_END
