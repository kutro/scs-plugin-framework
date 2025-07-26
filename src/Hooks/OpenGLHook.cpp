#include "SPF/Hooks/OpenGLHook.hpp"

#include <memory>

#include <windows.h>
#include <wingdi.h> // For wglSwapBuffers
#include <gl/GL.h>

#include "SPF/Memory/Detour.hpp"
#include "SPF/Logger/Logger.hpp"

#pragma comment(lib, "opengl32.lib")

SPF_NS_BEGIN

extern Logger* g_Logger;

using wglSwapBuffers_t = BOOL(WINAPI*)(HDC);

namespace
{
HMODULE opengl32;

std::unique_ptr<Detour> swapBuffersHook;

bool isInited = false;
} // namespace

BOOL __stdcall new_wglSwapBuffers(HDC hDc)
{
    if (!isInited)
    {
        if (OpenGLHook::OnInit) 
        {
            OpenGLHook::OnInit(hDc);
        }
        isInited = true;
    }

    if (OpenGLHook::OnPresent)
    {
        OpenGLHook::OnPresent(hDc);
    }

    return swapBuffersHook->getOriginal<wglSwapBuffers_t>()(hDc);
}

bool OpenGLHook::Install()
{
    opengl32 = GetModuleHandle(TEXT("opengl32.dll"));

    if (opengl32 == nullptr)
    {
        g_Logger->error("Cannot find opengl32.dll");
        return false;
    }

    g_Logger->info("Using OpenGL renderer");

    g_Logger->info("Hooking wglSwapBuffers...");

    swapBuffersHook = std::make_unique<Detour>(GetProcAddress(opengl32, "wglSwapBuffers"), new_wglSwapBuffers);

    if (auto err = swapBuffersHook->create(); err != Detour::Status::Ok)
    {
        g_Logger->error("Cannot create hook: {}", static_cast<int>(err));
        return false;
    }

    if (auto err = swapBuffersHook->enable(); err != Detour::Status::Ok)
    {
        g_Logger->error("Cannot enable hook: {}", static_cast<int>(err));
        return false;
    }

    return true;
}

void OpenGLHook::Uninstall()
{
    if (swapBuffersHook)
    {
        g_Logger->info("Restoring wglSwapBuffers...");
        swapBuffersHook->disable();
        swapBuffersHook->remove();
        swapBuffersHook.reset();
    }
}

SPF_NS_END
