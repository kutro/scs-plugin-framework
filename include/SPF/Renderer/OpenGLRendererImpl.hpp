#pragma once

#include <windows.h> // For HDC

#include "SPF/Renderer/Renderer.hpp"

SPF_NS_BEGIN

class OpenGLRendererImpl : public Renderer
{
private:
    bool _isInitialized = false;
    HDC _deviceContext = nullptr;

public:
    OpenGLRendererImpl(Core& core, EventManager& eventMgr);
    ~OpenGLRendererImpl();

    void init() override;

private:
    void onInit(HDC hdc);
    void onPresent(HDC hdc);
    // onResize is not a hook event, but can be triggered by other means if needed.
    // void onResize(int width, int height);
};

SPF_NS_END
