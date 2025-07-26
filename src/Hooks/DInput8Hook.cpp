#include "SPF/Hooks/DInput8Hook.hpp"

#include <dinput.h>
#include <windows.h>

#include <memory>
#include <vector>

#include "SPF/Logger/Logger.hpp"
#include "SPF/Memory/Detour.hpp"

SPF_NS_BEGIN

// Global logger instance
extern Logger* g_Logger;

// Define necessary GUIDs if not available
const GUID IID_IDirectInput8W_local = {
    0xbf798031, 0x483a, 0x4da2, {0xaa, 0x99, 0x5d, 0x64, 0xed, 0x36, 0x97, 0x00}};
const GUID GUID_SysMouseEm_local = {
    0x6F1D2B80, 0xD5A0, 0x11CF, {0xBF, 0xC7, 0x44, 0x45, 0x53, 0x54, 0x00, 0x00}};

// Type definitions for function pointers
using DirectInput8Create_t = HRESULT(WINAPI*)(
    HINSTANCE, DWORD, const IID&, LPVOID*, LPUNKNOWN);
using GetDeviceData_t = HRESULT(WINAPI*)(
    IDirectInputDevice8W*, DWORD, DIDEVICEOBJECTDATA*, LPDWORD, DWORD);

static std::unique_ptr<Detour> detour_GetDeviceData;

// This should be a static member of the class
bool DInput8Hook::DisableInGameMouse = false;

HRESULT WINAPI new_GetDeviceData(
    IDirectInputDevice8W* self,
    DWORD cbObjectData,
    DIDEVICEOBJECTDATA* rgdod,
    LPDWORD pdwInOut,
    DWORD dwFlags)
{
    HRESULT result = detour_GetDeviceData->getOriginal<GetDeviceData_t>()(
        self, cbObjectData, rgdod, pdwInOut, dwFlags);

    if (SUCCEEDED(result) && self != nullptr && rgdod != nullptr && pdwInOut != nullptr &&
        *pdwInOut > 0)
    {
        DIDEVICEINSTANCEW instance;
        instance.dwSize = sizeof(DIDEVICEINSTANCEW);
        if (SUCCEEDED(self->GetDeviceInfo(&instance)))
        {
            const auto deviceType = GET_DIDEVICE_TYPE(instance.dwDevType);

            if (deviceType == DI8DEVTYPE_MOUSE)
            {
                DInput8Hook::OnMouseData({rgdod, rgdod + (*pdwInOut)});

                if (DInput8Hook::DisableInGameMouse)
                {
                    *pdwInOut = 0; // Clear the data buffer
                }
            }
            else
            {
                DInput8Hook::OnJoystickData({rgdod, rgdod + (*pdwInOut)}, instance.guidInstance);
            }
        }
    }

    return result;
}

bool DInput8Hook::Install()
{
    HMODULE libDInput = ::GetModuleHandle(TEXT("dinput8.dll"));
    if (libDInput == nullptr)
    {
        g_Logger->error("Cannot find dinput8.dll");
        return false;
    }

    auto dInput8Create =
        reinterpret_cast<DirectInput8Create_t>(::GetProcAddress(libDInput, "DirectInput8Create"));
    if (dInput8Create == nullptr)
    {
        g_Logger->error("Cannot find DirectInput8Create inside dinput8.dll");
        return false;
    }

    IDirectInput8W* dinput = nullptr;
    if (FAILED(dInput8Create(
            GetModuleHandle(nullptr), DIRECTINPUT_VERSION, IID_IDirectInput8W_local,
            (void**)&dinput, nullptr)))
    {
        g_Logger->error("Cannot create DirectInput8 instance");
        return false;
    }

    IDirectInputDevice8W* mouse = nullptr;
    if (FAILED(dinput->CreateDevice(GUID_SysMouseEm_local, &mouse, nullptr)))
    {
        g_Logger->error("Cannot create DirectInput8 device for mouse");
        dinput->Release();
        return false;
    }

    // Get the address of GetDeviceData from the VTable
    void** vtable = *(void***)mouse;
    auto getDeviceDataAddr = vtable[10]; // GetDeviceData is the 10th function in the vtable

    g_Logger->info("Hooking IDirectInputDevice8::GetDeviceData...");
    detour_GetDeviceData =
        std::make_unique<Detour>(getDeviceDataAddr, &new_GetDeviceData);

    if (auto err = detour_GetDeviceData->create(); err != Detour::Status::Ok)
    {
        g_Logger->error("Cannot create GetDeviceData hook: {}", static_cast<int>(err));
        mouse->Release();
        dinput->Release();
        return false;
    }

    if (auto err = detour_GetDeviceData->enable(); err != Detour::Status::Ok)
    {
        g_Logger->error("Cannot enable GetDeviceData hook: {}", static_cast<int>(err));
        mouse->Release();
        dinput->Release();
        return false;
    }

    mouse->Release();
    dinput->Release();

    return true;
}

void DInput8Hook::Uninstall()
{
    if (detour_GetDeviceData)
    {
        g_Logger->info("Restoring IDirectInputDevice8::GetDeviceData...");
        detour_GetDeviceData->disable();
        detour_GetDeviceData->remove();
        detour_GetDeviceData.reset();
    }
}

SPF_NS_END
