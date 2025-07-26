#pragma once

#include "Namespace.hpp"
#include "SPF/Events/EventDispatcher.hpp" // For EventDispatcher

SPF_NS_BEGIN

class LoggerWindow
{
private:
    EventDispatcher& _eventMgr;
    bool _isEnabled = false;
    float _opacity = 1.0f;

public:
    LoggerWindow(EventDispatcher& eventMgr);

    void imguiRender();

    void setEnabled(bool enabled);
    void setOpacity(float opacity);
};

SPF_NS_END
