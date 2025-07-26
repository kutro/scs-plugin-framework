#include "SPF/Modules/ModuleManager.hpp"

SPF_NS_BEGIN

ModuleManager::ModuleManager(EventDispatcher& eventMgr, ConfigManager& configMgr, KeyBindsManager& keyBindsMgr, const Telemetry& telemetry)
    : _eventMgr(eventMgr), _configMgr(configMgr), _keyBindsMgr(keyBindsMgr), _telemetry(telemetry)
{
}

void ModuleManager::init()
{
    // TODO: Implement
}

// Other methods will be implemented later...

SPF_NS_END
