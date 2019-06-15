set(CMAKE_AUTOMOC ON)

set(SRCS
    main.cpp
    providessomething.cpp
)
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

qt5_add_resources(RESOURCES ../resources.qrc)

add_executable(qhot ${SRCS} ${RESOURCES})
target_link_libraries(qhot Qt5::Core Qt5::Qml Qt5::Widgets)
