TARGET = qhot

CONFIG += \
    c++17

win32 {
    # Enable console under windows
    CONFIG += console
}

QT += \
    core \
    charts \
    gui \
    network \
    opengl \
    printsupport \
    qml \
    quick \
    quickcontrols2 \
    quickwidgets \
    svg \
    widgets \
    xml \

include($$PWD/src/commandline/commandlineparser.pri)

HEADERS += \
    src/providessomething.h \
    src/urlinterceptor.h \

SOURCES += \
    src/main.cpp \
    src/providessomething.cpp \
    src/urlinterceptor.cpp \

RESOURCES += \
    resources.qrc
