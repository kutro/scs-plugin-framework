#pragma once

#include "Namespace.hpp"

SPF_NS_BEGIN

class EventManager; // Forward declaration

class EventProxyBase
{
protected:
    EventManager& _eventMgr;

public:
    EventProxyBase(EventManager& eventMgr);
    virtual ~EventProxyBase() = default;
};

SPF_NS_END
