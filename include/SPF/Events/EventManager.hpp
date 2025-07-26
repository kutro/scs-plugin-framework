#pragma once

#include <memory>
#include <vector>

#include <scssdk_telemetry.h>

#include "Namespace.hpp"

SPF_NS_BEGIN

// Forward declarations
struct EventDispatcher;
class EventAggregator;
class EventProxyBase;

class EventManager
{
private:
    std::unique_ptr<EventDispatcher> _dispatcher;
    std::unique_ptr<EventAggregator> _aggregator;
    std::vector<std::unique_ptr<EventProxyBase>> _eventProxies;

public:
    EventManager();
    ~EventManager(); // Required for pimpl/unique_ptr forward declaration

    void init(scs_telemetry_init_params_v100_t* scsTelemetry);

    // Provides access to the event sinks for subscription
    EventDispatcher& getDispatcher();
};

SPF_NS_END