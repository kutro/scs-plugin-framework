#include "SPF/Core.hpp"

#include <cstdio>
#include <filesystem>
#include <string>

#include <imgui.h>

#include "SPF/Config/Config.hpp"
#include "SPF/Config/ConfigManager.hpp"
#include "SPF/Events/EventManager.hpp"
#include "SPF/Input/InputManager.hpp"
#include "SPF/KeyBinding/KeyBindsManager.hpp"
#include "SPF/Logger/LoggerFactory.hpp"
#include "SPF/Modules/ModuleManager.hpp"
#include "SPF/Renderer/Renderer.hpp"
#include "SPF/SCSSDK/ChannelAggregator.hpp"
#include "SPF/UI/LoggerWindow.hpp"
#include "SPF/UI/MainWindow.hpp"
#include "SPF/Utils/Paths.hpp"
#include "SPF/Utils/Utils.hpp"
#include "SPF/Utils/Windows.hpp"

SPF_NS_BEGIN

// Global instance pointer for Core
static Core* g_CoreInstance = nullptr;

Core& Core::Get()
{
    return *g_CoreInstance;
}

Core::Core(HINSTANCE hInst)
    : _eventMgr(),
      _eventDispatcher(_eventMgr.getDispatcher()), // Get a reference to the dispatcher
      _channelAggregator(_eventDispatcher),
      _renderer(Renderer::Create(*this, _eventMgr)),
      _configMgr(),
      _keyBindsMgr(_eventDispatcher),
      _moduleMgr(_eventDispatcher, _configMgr, _keyBindsMgr, _channelAggregator.getTelemetry()),
      _mainWindow(_eventDispatcher),
      _loggerWindow(_eventDispatcher),
      _inputMgr(_eventDispatcher)
{
    g_CoreInstance = this;
    hInstance = hInst;
    _modulePath = Utils::GetModulePath(hInst);
}

Core::~Core()
{
    Logger->info("Deinitializing...");
}

bool Core::init(scs_telemetry_init_params_v100_t* scsTelemetry)
{
    Paths::Init(_modulePath);
    ImGui::GetIO().IniFilename = _strdup((Paths::HomePath + "\\imgui.ini").c_str());

    // Pass the dispatcher, not the manager
    LoggerFactory::Init(Paths::HomePath + "/spf_core.log", _eventDispatcher);
    Logger = LoggerFactory::GetLogger("core");

    Logger->info("API version {}", ApiVersion);
    Logger->info("Module's path: {}", Paths::ModulePath);
    Logger->info("Home path: {}", Paths::HomePath);

    _renderer->init();
    _eventMgr.init(scsTelemetry);
    _channelAggregator.init(scsTelemetry);
    _moduleMgr.init();
    _inputMgr.init();

    _isInited = true;
    scsTelemetry->common.log(SCS_LOG_TYPE_message, "[SPF-Framework] Initialized!");
    return true;
}

void Core::lateInit()
{
    Logger->info("Core successfully initialized!");
}

void Core::imguiRender()
{
    _mainWindow.imguiRender();
    _loggerWindow.imguiRender();

    // This is now called automatically by the EventAggregator,
    // so we don't need to call it manually here.
    // _eventDispatcher.system.onImGuiRender.call();
}

SPF_NS_END
