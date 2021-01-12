set(CMAKE_AUTOMOC ON)


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

get_target_property(QT_MOC_EXECUTABLE Qt5::moc LOCATION)
get_filename_component(QT_INSTALL_PREFIX ${QT_MOC_EXECUTABLE} DIRECTORY)
if (EXISTS ${QT_INSTALL_PREFIX})
    install(
        TARGETS qhot
        RUNTIME
        DESTINATION ${QT_INSTALL_PREFIX}
    )
endif()

