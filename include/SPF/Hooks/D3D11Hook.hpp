#pragma once

#include <cstdint>

#include <windows.h>

#include "SPF/Utils/Delegate.hpp"

struct IDXGISwapChain;
struct ID3D11Device;

SPF_NS_BEGIN

struct D3D11Hook
{
    inline static HWND hWnd;

    inline static Delegate<void(HWND, UINT, WPARAM, LPARAM)> OnWndProc;

    inline static Delegate<void(IDXGISwapChain*, ID3D11Device*)> OnInit;
    inline static Delegate<void(IDXGISwapChain*)> OnPresent;
    inline static Delegate<void(IDXGISwapChain*, uint32_t width, uint32_t height)> OnBeforeResize;
    inline static Delegate<void(IDXGISwapChain*)> OnResize;

    static bool Install();
    static void Uninstall();
};

SPF_NS_END
