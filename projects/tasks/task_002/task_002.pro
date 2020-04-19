TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    input.md.txt \
    output.md.txt \
    result.md.txt

