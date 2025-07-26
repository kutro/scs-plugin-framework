#pragma once

#include <cstdint>

#include "Namespace.hpp"

SPF_NS_BEGIN

enum class ButtonState
{
    Pressed,
    Released
};

struct MouseMoveEvent
{
    int x;
    int y;
};

struct MouseButtonEvent
{
    int button;
    ButtonState state;
};

struct MouseWheelEvent
{
    int wheel;
    int delta;
};

struct KeyboardEvent
{
    int key;
    ButtonState state;
};

struct OverlayStateEvent
{
    bool isEnabled;
};

SPF_NS_END
