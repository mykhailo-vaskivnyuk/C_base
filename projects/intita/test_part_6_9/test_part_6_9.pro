TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()

OTHER_FILES += \
    ../build/test_part_6_9/output_float.txt \
    ../build/test_part_6_9/output_integer.txt \
    ../build/test_part_6_9/input.txt

