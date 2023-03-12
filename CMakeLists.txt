project(qhot LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Qt6 REQUIRED
    Core
    Gui
    Qml
    Quick
    QuickControls2
)
qt_standard_project_setup()

add_subdirectory(src)
