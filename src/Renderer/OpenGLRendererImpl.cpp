#include "SPF/Renderer/OpenGLRendererImpl.hpp"

#include <imgui.h>
#include <imgui_impl_opengl3.h>
#include <imgui_impl_win32.h>
#include <windows.h> // For WindowFromDC

#include "SPF/Core.hpp"
#include "SPF/Hooks/OpenGLHook.hpp"
#include "SPF/Logger/Logger.hpp"

SPF_NS_BEGIN

extern Logger* g_Logger;

OpenGLRendererImpl::OpenGLRendererImpl(Core& core, EventManager& eventMgr)
    : Renderer(core, eventMgr)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGui::SetCurrentContext(ImGui::GetCurrentContext());
}

OpenGLRendererImpl::~OpenGLRendererImpl()
{
    if (!_isInitialized) return;

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();
}

void OpenGLRendererImpl::init()
{
    OpenGLHook::OnInit = {this, &OpenGLRendererImpl::onInit};
    OpenGLHook::OnPresent = {this, &OpenGLRendererImpl::onPresent};
}

void OpenGLRendererImpl::onInit(HDC hdc)
{
    _deviceContext = hdc;

    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;

    HWND hWnd = WindowFromDC(hdc);
    ImGui_ImplWin32_Init(hWnd);
    ImGui_ImplOpenGL3_Init("#version 130");

    g_Logger->info("OpenGL renderer initialized!");
    _isInitialized = true;
}

void OpenGLRendererImpl::onPresent(HDC hdc)
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplWin32_NewFrame();
    ImGui::NewFrame();

    _core.imguiRender();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

SPF_NS_END
