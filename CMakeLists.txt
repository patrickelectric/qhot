project(qhot LANGUAGES CXX)

cmake_minimum_required(VERSION 3.12)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(QHOT_USE_QT6 "Use Qt6" OFF)

if(QHOT_USE_QT6)
    set(QT_VERSION Qt6)
else()
    set(QT_VERSION Qt5)
endif()

find_package(${QT_VERSION} REQUIRED
    Core
    Gui
    Qml
    Quick
    QuickControls2
)

add_subdirectory(src)
