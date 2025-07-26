#include "SPF/SCSSDK/ChannelAggregator.hpp"

SPF_NS_BEGIN

ChannelAggregator::ChannelAggregator(EventDispatcher& eventDispatcher)
    : _eventDispatcher(eventDispatcher)
{
}

void ChannelAggregator::init(scs_telemetry_init_params_v100_t* scsTelemetry)
{
    // TODO: Implement
}

SPF_NS_END
