set(CMAKE_AUTOMOC ON)

# Automatically link Qt executables to qtmain target on Windows
cmake_policy(SET CMP0020 NEW)

qt5_add_resources(RESOURCES ../resources.qrc)

add_executable(qhot
    main.cpp
    providessomething.cpp
    urlinterceptor.cpp
    commandline/commandlineparser.cpp
    ${RESOURCES}
)

target_include_directories(qhot
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/commandline
)

target_link_libraries(qhot
    Qt5::Core
    Qt5::Gui
    Qt5::Qml
    Qt5::QuickControls2
)
