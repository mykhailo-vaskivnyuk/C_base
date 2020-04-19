TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.c \
    clubs.c \
    tree.c

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    clubs.h \
    tree.h

OTHER_FILES += \
    ../build/test_part_11_11/teams.txt

