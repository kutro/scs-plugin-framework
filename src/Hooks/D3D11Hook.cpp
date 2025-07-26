#include "SPF/Hooks/D3D11Hook.hpp"

#include <d3d11.h>
#include <wrl/client.h> // For Microsoft::WRL::ComPtr

#include "SPF/Logger/Logger.hpp"
#include "SPF/Memory/Detour.hpp"

#pragma comment(lib, "d3d11.lib")

SPF_NS_BEGIN

using Microsoft::WRL::ComPtr;

// Global logger from Core
extern Logger* g_Logger;

// --- Typedefs for original functions ---
using Present_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT);
using ResizeBuffers_t = HRESULT(STDMETHODCALLTYPE*)(IDXGISwapChain*, UINT, UINT, UINT, DXGI_FORMAT, UINT);

namespace
{
    WNDPROC g_oWndProc = nullptr;
    bool g_isPostInit = false;

    std::unique_ptr<Detour> g_presentHook;
    std::unique_ptr<Detour> g_resizeBuffersHook;

    // --- Hooked Functions ---

    LRESULT CALLBACK new_WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (D3D11Hook::OnWndProc)
        {
            D3D11Hook::OnWndProc(hWnd, uMsg, wParam, lParam);
        }
        return CallWindowProc(g_oWndProc, hWnd, uMsg, wParam, lParam);
    }

    HRESULT STDMETHODCALLTYPE new_Present(IDXGISwapChain* pSwapChain, UINT SyncInterval, UINT Flags)
    {
        if (!g_isPostInit)
        {
            ComPtr<ID3D11Device> pDevice;
            if (SUCCEEDED(pSwapChain->GetDevice(__uuidof(ID3D11Device), &pDevice)))
            {
                DXGI_SWAP_CHAIN_DESC desc;
                pSwapChain->GetDesc(&desc);
                D3D11Hook::hWnd = desc.OutputWindow;

                if (D3D11Hook::OnInit)
                {
                    D3D11Hook::OnInit(pSwapChain, pDevice.Get());
                }

                g_oWndProc = reinterpret_cast<WNDPROC>(SetWindowLongPtr(D3D11Hook::hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(new_WndProc)));
                g_isPostInit = true;
            }
        }

        if (D3D11Hook::OnPresent)
        {
            D3D11Hook::OnPresent(pSwapChain);
        }

        return g_presentHook->getOriginal<Present_t>()(pSwapChain, SyncInterval, Flags);
    }

    HRESULT STDMETHODCALLTYPE new_ResizeBuffers(IDXGISwapChain* pSwapChain, UINT BufferCount, UINT Width, UINT Height, DXGI_FORMAT NewFormat, UINT SwapChainFlags)
    {
        if (D3D11Hook::OnBeforeResize)
        {
            D3D11Hook::OnBeforeResize(pSwapChain, Width, Height);
        }

        HRESULT result = g_resizeBuffersHook->getOriginal<ResizeBuffers_t>()(pSwapChain, BufferCount, Width, Height, NewFormat, SwapChainFlags);

        if (SUCCEEDED(result) && D3D11Hook::OnResize)
        {
            D3D11Hook::OnResize(pSwapChain);
        }

        return result;
    }
}

bool D3D11Hook::Install()
{
    // 1. Create a dummy device and swap chain to get the vtable addresses
    WNDCLASSEX wc = { sizeof(WNDCLASSEX), CS_CLASSDC, DefWindowProc, 0L, 0L, GetModuleHandle(NULL), NULL, NULL, NULL, NULL, "DX11 Dummy", NULL };
    RegisterClassEx(&wc);
    HWND hWnd = CreateWindow(wc.lpszClassName, "DX11 Hook", WS_OVERLAPPEDWINDOW, 100, 100, 300, 300, NULL, NULL, wc.hInstance, NULL);

    DXGI_SWAP_CHAIN_DESC sd;
    ZeroMemory(&sd, sizeof(sd));
    sd.BufferCount = 1;
    sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    sd.OutputWindow = hWnd;
    sd.SampleDesc.Count = 1;
    sd.Windowed = TRUE;
    sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    ComPtr<ID3D11Device> pDevice;
    ComPtr<IDXGISwapChain> pSwapChain;
    D3D_FEATURE_LEVEL featureLevel;

    HRESULT hr = D3D11CreateDeviceAndSwapChain(NULL, D3D_DRIVER_TYPE_HARDWARE, NULL, 0, NULL, 0, D3D11_SDK_VERSION, &sd, &pSwapChain, &pDevice, &featureLevel, NULL);
    if (FAILED(hr))
    {
        DestroyWindow(hWnd);
        UnregisterClass(wc.lpszClassName, wc.hInstance);
        g_Logger->error("D3D11CreateDeviceAndSwapChain failed.");
        return false;
    }

    // 2. Get the vtable addresses from the dummy objects
    void** pSwapChainVTable = *(void***)pSwapChain.Get();
    void* pPresentAddr = pSwapChainVTable[8];
    void* pResizeBuffersAddr = pSwapChainVTable[13];

    // 3. Clean up dummy objects
    pDevice.Reset();
    pSwapChain.Reset();
    DestroyWindow(hWnd);
    UnregisterClass(wc.lpszClassName, wc.hInstance);

    // 4. Create and enable hooks
    g_Logger->info("Hooking D3D11 Present...");
    g_presentHook = std::make_unique<Detour>(pPresentAddr, new_Present);
    g_presentHook->create();
    g_presentHook->enable();

    g_Logger->info("Hooking D3D11 ResizeBuffers...");
    g_resizeBuffersHook = std::make_unique<Detour>(pResizeBuffersAddr, new_ResizeBuffers);
    g_resizeBuffersHook->create();
    g_resizeBuffersHook->enable();

    return true;
}

void D3D11Hook::Uninstall()
{
    g_Logger->info("Uninstalling D3D11 hooks...");
    g_presentHook.reset();
    g_resizeBuffersHook.reset();

    if (g_oWndProc && hWnd)
    {
        SetWindowLongPtr(hWnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(g_oWndProc));
    }
    g_oWndProc = nullptr;
}

SPF_NS_END