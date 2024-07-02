# Automatically link Qt executables to qtmain target on Windows
cmake_policy(SET CMP0020 NEW)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

qt6_add_resources(RESOURCES ../resources.qrc)

add_executable(qhot
    main.cpp
    providessomething.cpp
    urlinterceptor.cpp
    commandline/commandlineparser.cpp
    ${RESOURCES}
)

set_target_properties(qhot PROPERTIES CXX_STANDARD ${CMAKE_CXX_STANDARD})

target_include_directories(qhot
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/commandline
)

target_link_libraries(qhot
    Qt6::Core
    Qt6::Gui
    Qt6::Qml
    Qt6::QuickControls2
    Qt6::Widgets
)

get_target_property(QT_MOC_EXECUTABLE Qt6::moc IMPORTED_LOCATION)
get_filename_component(QT_INSTALL_PREFIX ${QT_MOC_EXECUTABLE} DIRECTORY)
if (EXISTS ${QT_INSTALL_PREFIX})
    install(
        TARGETS qhot
        RUNTIME
        DESTINATION ${QT_INSTALL_PREFIX}
    )
endif()

set_target_properties(qhot PROPERTIES MACOSX_BUNDLE ON)
