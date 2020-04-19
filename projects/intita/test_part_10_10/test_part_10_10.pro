TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    clubs.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    clubs.h

