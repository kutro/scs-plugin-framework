cmake_minimum_required(VERSION 3.15)
cmake_policy(SET CMP0091 NEW)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(SPF-Framework VERSION 1.0.0)

add_subdirectory(vendor)

# Core library
set(SPF_CORE_SOURCES
    src/Core.cpp
    src/dllmain.cpp
    src/Config/Config.cpp
    src/Config/ConfigManager.cpp
    src/Events/EventManager.cpp
    src/Hooks/D3D11Hook.cpp
    src/Hooks/DInput8Hook.cpp
    src/Hooks/OpenGLHook.cpp
    src/Input/InputManager.cpp
    src/KeyBinding/KeyBinds.cpp
    src/KeyBinding/KeyBindsManager.cpp
    src/Logger/Logger.cpp
    src/Logger/LoggerFactory.cpp
    src/Memory/Detour.cpp
    src/Memory/Hooking.Patterns.cpp
    src/Modules/ModuleManager.cpp
    src/Renderer/Renderer.cpp
    src/Renderer/D3D11RendererImpl.cpp
    src/Renderer/OpenGLRendererImpl.cpp
    src/SCSSDK/ChannelAggregator.cpp
    src/System/Mouse.cpp
    src/UI/MainWindow.cpp
    src/UI/LoggerWindow.cpp
    src/Utils/Paths.cpp
    src/Utils/Utils.cpp
    src/Utils/Windows.cpp
)

add_library(SPF-Framework SHARED ${SPF_CORE_SOURCES})

target_compile_definitions(SPF-Framework PUBLIC _USE_MATH_DEFINES)
target_compile_definitions(SPF-Framework PRIVATE SPF_EXPORT _CRT_SECURE_NO_WARNINGS WIN32_LEAN_AND_MEAN NOMINMAX)

if(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
  target_compile_options(
    SPF-Framework
    PUBLIC -Wnon-virtual-dtor
           -Wunused
           -Woverloaded-virtual
           -Wnull-dereference
           -Wdouble-promotion
           -Wformat=2
           -Wmisleading-indentation
           -Wparentheses
           -Wswitch
           -Wswitch-bool
           -Wextra
           -Wpedantic)
endif()

target_include_directories(SPF-Framework PUBLIC
    ${CMAKE_SOURCE_DIR}/include
    vendor/json/include
    vendor/imgui
    vendor/scs_sdk/include
)
target_link_libraries(SPF-Framework PUBLIC fmt::fmt-header-only imgui glad minhook)
