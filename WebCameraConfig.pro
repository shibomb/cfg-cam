QT -= gui

CONFIG += c++11

# Fix for std::byte conflict with Windows API
DEFINES += WIN32_LEAN_AND_MEAN
DEFINES += NOMINMAX

TARGET = WebCameraConfig
CONFIG += console
CONFIG -= app_bundle

# Disable C++17 std::byte
QMAKE_CXXFLAGS += -fno-char8_t
QMAKE_CXXFLAGS += -std=c++11

# Static linking to avoid DLL dependencies
QMAKE_LFLAGS += -static
QMAKE_LFLAGS += -static-libgcc
QMAKE_LFLAGS += -static-libstdc++

TEMPLATE = app

SOURCES += \
    main.cpp \
    loginfo.cpp \
    camset.cpp

# The following define makes your compiler emit warnings if you use
# any feature of Qt which as been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

HEADERS += \
    loginfo.h \
    camset.h

# Windows API libraries
LIBS += -lole32 -loleaut32 -lstrmiids
