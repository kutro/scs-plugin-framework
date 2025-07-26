#pragma once

#include <scssdk_telemetry.h>
#include <windows.h>

#include <memory>
#include <string>

#include "SPF/Config/ConfigManager.hpp"
#include "SPF/Events/EventManager.hpp"
#include "GameType.hpp"
#include "SPF/Input/InputManager.hpp"
#include "SPF/KeyBinding/KeyBindsManager.hpp"
#include "SPF/Logger/Logger.hpp"
#include "SPF/Modules/ModuleManager.hpp"
#include "Namespace.hpp"
#include "SPF/Renderer/Renderer.hpp"
#include "SPF/SCSSDK/ChannelAggregator.hpp"
#include "SPF/UI/LoggerWindow.hpp"
#include "SPF/UI/MainWindow.hpp"
#include "Version.hpp"

SPF_NS_BEGIN

// Forward declarations
struct EventDispatcher;
class Config;
class KeyBinds;

class Core
{
public:
    static Core& Get();

public:
    inline static HINSTANCE hInstance;
    inline static std::unique_ptr<Logger> Logger;
    inline static GameType GameType;

private:
    bool _isInited = false;
    std::string _modulePath;

    EventManager _eventMgr;
    EventDispatcher& _eventDispatcher; // Changed to a reference
    ChannelAggregator _channelAggregator;
    std::unique_ptr<Renderer> _renderer;
    ConfigManager _configMgr;
    KeyBindsManager _keyBindsMgr;
    ModuleManager _moduleMgr;
    MainWindow _mainWindow;
    LoggerWindow _loggerWindow;
    InputManager _inputMgr;

    std::unique_ptr<Config> _coreConfig;
    std::unique_ptr<KeyBinds> _coreKeyBinds;

public:
    explicit Core(HINSTANCE hInst);
    ~Core();

    bool init(scs_telemetry_init_params_v100_t* scsTelemetry);
    void lateInit();
    void imguiRender();

    [[nodiscard]] bool isInited() const { return _isInited; }
    [[nodiscard]] InputManager& getInputManager() { return _inputMgr; }

private:
    // Private methods to be implemented later
    void initConfig();
    void initKeyBinds();
};

SPF_NS_END
