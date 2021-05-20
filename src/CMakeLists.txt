set(CMAKE_AUTOMOC ON)

# Automatically link Qt executables to qtmain target on Windows
cmake_policy(SET CMP0020 NEW)

if(QHOT_USE_QT6)
    qt6_add_resources(RESOURCES ../resources.qrc)
else()
    qt5_add_resources(RESOURCES ../resources.qrc)
endif()

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
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Qml
    Qt${QT_VERSION_MAJOR}::QuickControls2
)

get_target_property(QT_MOC_EXECUTABLE Qt${QT_VERSION_MAJOR}::moc LOCATION)
get_filename_component(QT_INSTALL_PREFIX ${QT_MOC_EXECUTABLE} DIRECTORY)
if (EXISTS ${QT_INSTALL_PREFIX})
    install(
        TARGETS qhot
        RUNTIME
        DESTINATION ${QT_INSTALL_PREFIX}
    )
endif()

