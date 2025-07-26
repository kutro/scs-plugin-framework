#pragma once

#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/KeyBinding/KeyBinds.hpp"
#include "Namespace.hpp"

SPF_NS_BEGIN

class KeyBind; // Forward declaration

class MainWindow
{
private:
    bool _isWindowVisible = false;
    KeyBind* _showMainWindowKeyBind{};

public:
    explicit MainWindow(EventDispatcher& eventDispatcher);

    void initKeyBinds(KeyBinds& keyBinds);
    void imguiRender();

private:
    void toggle(ButtonState);
};

SPF_NS_END
