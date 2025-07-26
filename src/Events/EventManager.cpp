#include "SPF/Events/EventManager.hpp"
#include "SPF/Events/EventProxyBase.hpp"

#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/Hooks/D3D11Hook.hpp"
#include "SPF/Hooks/DInput8Hook.hpp"
#include "SPF/Hooks/OpenGLHook.hpp"

SPF_NS_BEGIN

// --- Implementation Detail: EventAggregator ---
// This class's only job is to listen to raw hook events and push them
// into the correct sinks in the public EventDispatcher.
class EventAggregator
{
private:
    EventDispatcher& _dispatcher;

public:
    explicit EventAggregator(EventDispatcher& dispatcher)
        : _dispatcher(dispatcher)
    {
        // Connect hook events to dispatcher sinks
        DInput8Hook::OnMouseData = {this, &EventAggregator::onMouseData};
        D3D11Hook::OnPresent = {this, &EventAggregator::onD3D11Present};
        OpenGLHook::OnPresent = {this, &EventAggregator::onOpenGLPresent};
    }

    void onMouseData(const std::vector<DIDEVICEOBJECTDATA>&& events)
    {
        // Here you could process the raw data before dispatching, if needed.
        // For now, we just forward it.
    }

    void onD3D11Present(IDXGISwapChain* swapChain)
    {
        onRender();
    }

    void onOpenGLPresent(HDC hdc)
    {
        onRender();
    }

    void onRender()
    {
        // This single handler is called by any renderer hook.
        _dispatcher.system.onImGuiRender.call();
    }
};
// --- End of Implementation Detail ---

EventManager::EventManager()
{
    _dispatcher = std::make_unique<EventDispatcher>();
    _aggregator = std::make_unique<EventAggregator>(*_dispatcher);
}

EventManager::~EventManager() = default; // Needed for unique_ptr with forward-declared types

void EventManager::init(scs_telemetry_init_params_v100_t* scsTelemetry)
{
    // Logic for initializing event proxies would go here
}

EventDispatcher& EventManager::getDispatcher()
{
    return *_dispatcher;
}

SPF_NS_END
