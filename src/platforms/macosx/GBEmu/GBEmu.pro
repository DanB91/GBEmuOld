#-------------------------------------------------
#
# Project created by QtCreator 2013-08-10T17:04:52
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
    ../../../Emulator/Cartridge.cpp

HEADERS  += mainwindow.h \
    ../../../Emulator/types.h \
    ../../../Emulator/opcodes.h \
    ../../../Emulator/MMU.h \
    ../../../Emulator/GBEmuExceptions.h \
    ../../../Emulator/GameBoy.h \
    ../../../Emulator/CPU.h \
    ../../../Emulator/Cartridge.h

FORMS    += mainwindow.ui

QMAKE_CXXFLAGS += -std=c++11
CONFIG+=c++11
