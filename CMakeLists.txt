
cmake_minimum_required(VERSION 3.16)

project(LadoA_R36S VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED IMPORTED_TARGET sdl2)

add_executable(ladoa
    src/main.cpp
    src/ui/CoverFlow.cpp
    src/debug/FPSCounter.cpp
     src/debug/PerformanceLogger.cpp
)

target_link_libraries(ladoa PRIVATE PkgConfig::SDL2)
