TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../build/test_part_9_3/teams.txt

