file(GLOB imgui_src
    imgui/*.cpp
    imgui/*.h
    imgui/backends/imgui_impl_dx11.cpp
    imgui/backends/imgui_impl_dx11.h
    imgui/backends/imgui_impl_opengl3.cpp
    imgui/backends/imgui_impl_opengl3.h
    imgui/backends/imgui_impl_win32.cpp
    imgui/backends/imgui_impl_win32.h
    imgui/misc/cpp/imgui_stdlib.cpp
    imgui/misc/cpp/imgui_stdlib.h
)

add_library(imgui STATIC ${imgui_src})

target_include_directories(imgui PUBLIC imgui imgui/backends imgui/misc/cpp)
