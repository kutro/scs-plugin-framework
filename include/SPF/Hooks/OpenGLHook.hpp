#pragma once

#include <cstdint>

#include <windows.h>

#include "SPF/Utils/Delegate.hpp"

SPF_NS_BEGIN

struct OpenGLHook
{
    inline static Delegate<void(HWND, UINT, WPARAM, LPARAM)> OnWndProc;
    inline static Delegate<void(HDC)> OnInit;
    inline static Delegate<void(HDC)> OnPresent;
    inline static Delegate<void(int, int)> OnResize;

    static bool Install();
    static void Uninstall();
};

SPF_NS_END
