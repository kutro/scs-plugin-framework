#pragma once

#include "Namespace.hpp"

SPF_NS_BEGIN

namespace Mouse
{
    enum class Button
    {
        Left,
        Right,
        Middle,
        Button4,
        Button5,
        Button6,
        Button7,
        Button8
    };

    enum class Wheel
    {
        Vertical,
        Horizontal
    };

    void DisableInGameMouse(bool disable);
} // namespace Mouse

SPF_NS_END
