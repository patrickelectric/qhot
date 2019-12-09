TARGET = qhot

CONFIG += \
    c++14

win32 {
    # Enable console under windows
    CONFIG += console
}

QT += \
    gui \
    network \
    opengl \
    printsupport \
    qml \
    quick \
    quickwidgets \
    svg \
    widgets \
    xml \

HEADERS += \
    src/providessomething.h \
    src/urlinterceptor.h \

SOURCES += \
    src/main.cpp \
    src/providessomething.cpp \
    src/urlinterceptor.cpp \

RESOURCES += \
    resources.qrc
