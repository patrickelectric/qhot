TARGET = qhot

CONFIG += \
    c++14

win32 {
    # Enable console under windows
    CONFIG += console
}

QT += gui qml widgets

HEADERS += \
    src/providessomething.h \
    src/urlinterceptor.h \

SOURCES += \
    src/main.cpp \
    src/providessomething.cpp \
    src/urlinterceptor.cpp \

RESOURCES += \
    resources.qrc
