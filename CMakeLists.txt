project(qhot)

cmake_minimum_required(VERSION 2.8)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt5 REQUIRED
    Core
    Qml
    Quick
    QuickControls2
    Widgets
)

add_subdirectory(src)
