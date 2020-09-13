set(CMAKE_AUTOMOC ON)

set(SRCS
    main.cpp
    providessomething.cpp
    urlinterceptor.cpp
    commandline/commandlineparser.cpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/commandline)

qt5_add_resources(RESOURCES ../resources.qrc)

add_executable(qhot ${SRCS} ${RESOURCES})
target_link_libraries(qhot Qt5::Core Qt5::Qml Qt5::QuickControls2 Qt5::Widgets)
