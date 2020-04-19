TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    stack.c \
    clubs.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    stack.h \
    clubs.h

