#pragma once

#include "Namespace.hpp"
#include "SPF/Utils/Delegate.hpp"
#include "SPF/Events/Event.hpp"

SPF_NS_BEGIN

struct EventDispatcher
{
    struct
    {
        Sink<const MouseMoveEvent&> onMouseMove;
        Sink<const MouseButtonEvent&> onMouseButtonPress;
        Sink<const MouseButtonEvent&> onMouseButtonRelease;
        Sink<const MouseWheelEvent&> onMouseWheelScroll;
        Sink<const KeyboardEvent&> onKeyPress;
        Sink<const KeyboardEvent&> onKeyRelease;
        Sink<> onImGuiRender; // Changed from Sink<void()>
        Sink<const OverlayStateEvent&> onOverlayStateChange;
    } system;
};

SPF_NS_END
