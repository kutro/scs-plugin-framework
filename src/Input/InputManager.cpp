#include "SPF/Input/InputManager.hpp"

#include <imgui.h>

#include "SPF/System/Mouse.hpp"
#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/Hooks/DInput8Hook.hpp"

// These are offsets within the DIMOUSESTATE2 structure
// They are not defined in dinput.h directly as constants, so we define them here
// This is a common pattern when working with DirectInput raw data
constexpr int DI_MOUSE_X = offsetof(DIMOUSESTATE2, lX);
constexpr int DI_MOUSE_Y = offsetof(DIMOUSESTATE2, lY);
constexpr int DI_MOUSE_Z = offsetof(DIMOUSESTATE2, lZ);
constexpr int DI_MOUSE_BUTTON_0 = (offsetof(DIMOUSESTATE2, rgbButtons) + 0);
constexpr int DI_MOUSE_BUTTON_1 = (offsetof(DIMOUSESTATE2, rgbButtons) + 1);
constexpr int DI_MOUSE_BUTTON_2 = (offsetof(DIMOUSESTATE2, rgbButtons) + 2);

SPF_NS_BEGIN

InputManager::InputManager(EventDispatcher& eventMgr) : _eventMgr(eventMgr)
{
}

void InputManager::init()
{
    DInput8Hook::OnMouseData = {this, &InputManager::onDInputMouse};
}

void InputManager::setEnabled(bool isEnabled)
{
    if (_isEnabled == isEnabled) return;

    _isEnabled = isEnabled;

    auto& io = ImGui::GetIO();
    io.MouseDrawCursor = isEnabled; // ImGui draws its own cursor

    Mouse::DisableInGameMouse(isEnabled); // Tell the game to stop processing mouse input
}

void InputManager::onDInputMouse(const std::vector<DIDEVICEOBJECTDATA>&& events)
{
    if (!_isEnabled) return;

    auto& io = ImGui::GetIO();

    for (const auto& event : events)
    {
        switch (event.dwOfs)
        {
            case DI_MOUSE_X:
                io.MousePos.x += static_cast<float>(event.dwData);
                break;
            case DI_MOUSE_Y:
                io.MousePos.y += static_cast<float>(event.dwData);
                break;
            case DI_MOUSE_Z:
                io.MouseWheel += static_cast<short>(static_cast<short>(event.dwData) / WHEEL_DELTA);
                break;
            case DI_MOUSE_BUTTON_0:
                io.MouseDown[0] = (event.dwData & 0x80) ? true : false;
                break;
            case DI_MOUSE_BUTTON_1:
                io.MouseDown[1] = (event.dwData & 0x80) ? true : false;
                break;
            case DI_MOUSE_BUTTON_2:
                io.MouseDown[2] = (event.dwData & 0x80) ? true : false;
                break;
        }
    }
}

SPF_NS_END
