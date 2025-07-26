#pragma once

#include <string>
#include <vector>
#include <memory>

#include "Namespace.hpp"
#include "SPF/Events/EventDispatcher.hpp"
#include "SPF/Config/ConfigManager.hpp" // Assuming this will be created later
#include "SPF/KeyBinding/KeyBindsManager.hpp"
#include "SPF/SCSSDK/Telemetry.hpp" // Assuming this will be created later

SPF_NS_BEGIN

class Module
{
public:
    std::string dllName;
    // Add more module info here
};

class ModuleManager
{
private:
    EventDispatcher& _eventMgr;
    ConfigManager& _configMgr;
    KeyBindsManager& _keyBindsMgr;
    const Telemetry& _telemetry;

    std::vector<std::unique_ptr<Module>> _modules;

public:
    ModuleManager(EventDispatcher& eventMgr, ConfigManager& configMgr, KeyBindsManager& keyBindsMgr, const Telemetry& telemetry);

    void init();
    void scan();
    void load(Module* module);
    void unload(Module* module);

    const std::vector<std::unique_ptr<Module>>& getModules() const { return _modules; }
};

SPF_NS_END
