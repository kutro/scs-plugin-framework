#include "SPF/UI/MainWindow.hpp"

#include <imgui.h>

#include "SPF/Core.hpp"
#include "SPF/Input/InputManager.hpp"

SPF_NS_BEGIN

MainWindow::MainWindow(EventDispatcher& eventDispatcher)
{
    // Explicitly create the delegate to resolve ambiguity
    eventDispatcher.system.onImGuiRender.connect(Delegate<void()>{this, &MainWindow::imguiRender});
}

void MainWindow::initKeyBinds(KeyBinds& keyBinds)
{
    // Use the new, cleaner API for adding keybinds
    keyBinds.add("show_main_window")
        .setLabel("Show main window")
        .setDefaultKey(Keyboard::Key::Delete)
        .setPressCallback({this, &MainWindow::toggle});
}

void MainWindow::imguiRender()
{
    if (!_isWindowVisible)
    {
        return;
    }

    ImGui::SetNextWindowSize({600.f, 400.f}, ImGuiCond_FirstUseEver);

    if (ImGui::Begin("SPF Framework", &_isWindowVisible, ImGuiWindowFlags_NoCollapse))
    {
        ImGui::Text("SPF Framework is running.");
        ImGui::Text("ImGui Version: %s", IMGUI_VERSION);
    }

    ImGui::End();
}

void MainWindow::toggle(ButtonState /*unused*/)
{
    _isWindowVisible = !_isWindowVisible;
    Core::Get().getInputManager().setEnabled(_isWindowVisible);
    // The event call for overlay state change should be handled here if needed
    // For now, we just toggle visibility and input
}

SPF_NS_END
