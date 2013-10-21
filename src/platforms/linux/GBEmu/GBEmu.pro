#-------------------------------------------------
#
# Project created by QtCreator 2013-08-11T22:07:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = GBEmu
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ../../../Emulator/MMU.cpp \
    ../../../Emulator/GameBoy.cpp \
    ../../../Emulator/CPU.cpp \
    ../../../Emulator/Cartridge.cpp \
    cpucontrolwindow.cpp \
    ../../../Emulator/CPUDebugInfo.cpp \
    ../../../Emulator/Screen.cpp \
    GUIPixel.cpp \
    ../../../Emulator/GPU.cpp \
    ../../../Emulator/opcodes.cpp \

HEADERS  += mainwindow.h \
    ../../../Emulator/types.h \
    ../../../Emulator/MMU.h \
    ../../../Emulator/GBEmuExceptions.h \
    ../../../Emulator/GameBoy.h \
    ../../../Emulator/CPU.h \
    ../../../Emulator/Cartridge.h \
    cpucontrolwindow.h \
    ../../../Emulator/CPUDebugInfo.h \
    ../../../Emulator/Screen.h \
    GUIPixel.h \
    ../../../Emulator/GPU.h

FORMS    += mainwindow.ui \
    cpucontrolwindow.ui

INCLUDEPATH += ../../..

QMAKE_CXXFLAGS += -std=c++11
CONFIG += c++11
