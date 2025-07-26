#pragma once

#include "Namespace.hpp"
#include "SPF/Events/EventDispatcher.hpp"
#include "Telemetry.hpp" // Assuming this will be created later

SPF_NS_BEGIN

class ChannelAggregator
{
private:
    EventDispatcher& _eventDispatcher;
    Telemetry _telemetry;

public:
    ChannelAggregator(EventDispatcher& eventDispatcher);

    void init(scs_telemetry_init_params_v100_t* scsTelemetry);

    const Telemetry& getTelemetry() const { return _telemetry; }
};

SPF_NS_END
