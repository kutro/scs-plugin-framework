#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Namespace.hpp"
#include "SPF/KeyBinding/KeyBinds.hpp"
#include "SPF/Events/EventDispatcher.hpp"

SPF_NS_BEGIN

class KeyBindsManager
{
private:
    EventDispatcher& _eventDispatcher;
    std::vector<std::unique_ptr<KeyBinds>> _keyBinds;

public:
    KeyBindsManager(EventDispatcher& eventDispatcher);

    KeyBinds& createKeyBinds(const std::string& name);

    const std::vector<std::unique_ptr<KeyBinds>>& getKeyBinds() const { return _keyBinds; }

    void saveAll();
    void loadAll();
};

SPF_NS_END
