TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    test.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    test.h

