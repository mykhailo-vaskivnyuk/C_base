TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

HEADERS +=

OTHER_FILES += \
    ../build/test_part_0_4/sur.txt \
    ../build/test_part_0_4/names.txt \
    ../build/test_part_0_4/res.txt

