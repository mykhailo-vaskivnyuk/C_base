TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

QMAKE += -std-C99

include(deployment.pri)
qtcAddDeployment()

