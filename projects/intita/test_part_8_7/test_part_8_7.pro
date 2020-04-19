TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../build/test_part_8_7/teams.dat \
    ../build/test_part_8_7/teams_new.dat

