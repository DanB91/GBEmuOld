#-------------------------------------------------
#
# Project created by QtCreator 2013-08-11T22:18:12
#
#-------------------------------------------------

QT       += testlib

QT       -= gui

TARGET = tst_gbemutest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += \
    main.cpp \
    ../../../Emulator/MMU.cpp \
    ../../../Emulator/GameBoy.cpp \
    ../../../Emulator/CPU.cpp \
    ../../../Emulator/Cartridge.cpp \
    cputest.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    CartridgeTest.h \
    AutoTest.h \
    ../../../Emulator/types.h \
    ../../../Emulator/MMU.h \
    ../../../Emulator/GBEmuExceptions.h \
    ../../../Emulator/GameBoy.h \
    ../../../Emulator/CPU.h \
    ../../../Emulator/Cartridge.h \
    MMUTest.h \
    cputest.h

INCLUDEPATH += ../../../Emulator
QMAKE_CXXFLAGS += -std=c++11
