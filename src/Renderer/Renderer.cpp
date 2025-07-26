#include "SPF/Renderer/Renderer.hpp"

#include <windows.h>

#include "SPF/Renderer/D3D11RendererImpl.hpp"
#include "SPF/Renderer/OpenGLRendererImpl.hpp"

SPF_NS_BEGIN

Renderer::Renderer(Core& core, EventManager& eventMgr)
    : _core(core), _eventMgr(eventMgr)
{
}

std::unique_ptr<Renderer> Renderer::Create(Core& core, EventManager& eventMgr)
{
    if (GetModuleHandleA("d3d11.dll"))
    {
        return std::make_unique<D3D11RendererImpl>(core, eventMgr);
    }
    
    if (GetModuleHandleA("opengl32.dll"))
    {
        return std::make_unique<OpenGLRendererImpl>(core, eventMgr);
    }

    // If no renderer is available, return nullptr. The core should handle this.
    return nullptr;
}

SPF_NS_END
