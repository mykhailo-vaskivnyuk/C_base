TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    clubs.c \
    queue.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    clubs.h \
    queue.h

