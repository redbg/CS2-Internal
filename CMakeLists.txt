cmake_minimum_required(VERSION 3.21)

set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# ImGui
file(GLOB IMGUI_SRC imgui/*.cpp)

# CS2-Internal.dll
project(CS2-Internal)
add_library(CS2-Internal SHARED
    src/DllMain.cpp
    ${IMGUI_SRC}
)

target_include_directories(CS2-Internal
    PRIVATE src/include
    PRIVATE src/CS2
    PRIVATE src/CS2/Class
    PRIVATE imgui
)

# CS2-Injector.exe
project(CS2-Injector)
add_executable(CS2-Injector src/Injector.cpp)
