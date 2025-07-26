#pragma once

#include <memory>

#include "Namespace.hpp"

SPF_NS_BEGIN

class Core;
class EventManager;

class Renderer
{
protected:
    Core& _core;
    EventManager& _eventMgr;

public:
    Renderer(Core& core, EventManager& eventMgr);
    virtual ~Renderer() = default;

    virtual void init() = 0;

    // Factory method to create the appropriate renderer implementation
    static std::unique_ptr<Renderer> Create(Core& core, EventManager& eventMgr);
};

SPF_NS_END
