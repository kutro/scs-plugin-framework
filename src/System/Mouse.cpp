#include "SPF/System/Mouse.hpp"

#include "SPF/Hooks/DInput8Hook.hpp"

SPF_NS_BEGIN

void Mouse::DisableInGameMouse(bool disable)
{
    DInput8Hook::DisableInGameMouse = disable;
}

SPF_NS_END
