#pragma once

#include "SPF/Renderer/Renderer.hpp"

struct IDXGISwapChain;
struct ID3D11Device;
struct ID3D11DeviceContext;

SPF_NS_BEGIN

class D3D11RendererImpl : public Renderer
{
private:
    bool _isInitialized = false;
    IDXGISwapChain* _swapChain;
    ID3D11Device* _device;
    ID3D11DeviceContext* _deviceContext;

public:
    D3D11RendererImpl(Core& core, EventManager& eventMgr);
    ~D3D11RendererImpl();

    void init() override;

private:
    void onInit(IDXGISwapChain* swapChain, ID3D11Device* device);
    void onPresent(IDXGISwapChain* swapChain);
    void onResize(IDXGISwapChain* swapChain);
};

SPF_NS_END
