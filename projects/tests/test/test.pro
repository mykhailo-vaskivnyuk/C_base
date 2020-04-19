TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

CONFIG += -std=c99
QMAKE_LFLAGS += -static-libgcc

