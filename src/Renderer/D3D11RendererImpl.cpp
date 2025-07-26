#include "SPF/Renderer/D3D11RendererImpl.hpp"

#include <d3d11.h>
#include <imgui.h>
#include <imgui_impl_dx11.h>
#include <imgui_impl_win32.h>

#include "SPF/Core.hpp"
#include "SPF/Hooks/D3D11Hook.hpp"
#include "SPF/Logger/Logger.hpp"

SPF_NS_BEGIN

extern Logger* g_Logger;

D3D11RendererImpl::D3D11RendererImpl(Core& core, EventManager& eventMgr)
    : Renderer(core, eventMgr)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
}

D3D11RendererImpl::~D3D11RendererImpl()
{
    if (!_isInitialized) return;

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void D3D11RendererImpl::init()
{
    // Assign our methods as the callbacks for the hooks
    D3D11Hook::OnInit = {this, &D3D11RendererImpl::onInit};
    D3D11Hook::OnPresent = {this, &D3D11RendererImpl::onPresent};
    D3D11Hook::OnResize = {this, &D3D11RendererImpl::onResize};
}

void D3D11RendererImpl::onInit(IDXGISwapChain* swapChain, ID3D11Device* device)
{
    _swapChain = swapChain;
    _device = device;

    _device->GetImmediateContext(&_deviceContext);

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard; // Enable Keyboard Controls
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;  // Enable Gamepad Controls

    ImGui_ImplWin32_Init(D3D11Hook::hWnd);
    ImGui_ImplDX11_Init(_device, _deviceContext);

    g_Logger->info("D3D11 renderer initialized!");
    _isInitialized = true;
}

void D3D11RendererImpl::onPresent(IDXGISwapChain* swapChain)
{
    ImGui_ImplDX11_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    _core.imguiRender();

    ImGui::Render();
    ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
}

void D3D11RendererImpl::onResize(IDXGISwapChain* swapChain)
{
    ImGui_ImplDX11_InvalidateDeviceObjects();

    if (_deviceContext)
    {
        _deviceContext->Release();
        _deviceContext = nullptr;
    }

    // Get new device context
    _device->GetImmediateContext(&_deviceContext);

    ImGui_ImplDX11_CreateDeviceObjects();
}

SPF_NS_END
