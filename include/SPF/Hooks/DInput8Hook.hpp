#pragma once

#include <vector>
#include <dinput.h> // For DIDEVICEOBJECTDATA
#include <windows.h> // For HWND, UINT, WPARAM, LPARAM

#include "SPF/Utils/Delegate.hpp" // For Delegate

SPF_NS_BEGIN

struct DInput8Hook
{
    inline static Delegate<void(const std::vector<DIDEVICEOBJECTDATA>&&)> OnMouseData;
    inline static Delegate<void(const std::vector<DIDEVICEOBJECTDATA>&&, const GUID&)> OnJoystickData;

    static bool DisableInGameMouse;

    static bool Install();
    static void Uninstall();
};

SPF_NS_END
