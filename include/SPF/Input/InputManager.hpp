#pragma once

#include <vector>

#include <dinput.h> // For DIDEVICEOBJECTDATA

#include "Namespace.hpp"
#include "SPF/Events/EventDispatcher.hpp" // For EventDispatcher

SPF_NS_BEGIN

class InputManager
{
private:
    EventDispatcher& _eventMgr;
    bool _isEnabled = false;

public:
    InputManager(EventDispatcher& eventMgr);

    void init();

    void setEnabled(bool isEnabled);

private:
    void onDInputMouse(const std::vector<DIDEVICEOBJECTDATA>&& events);
};

SPF_NS_END
