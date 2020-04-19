TEMPLATE = app
//CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

//QT += opengl
LIBS += -lopengl32

SOURCES += main.c

include(deployment.pri)
qtcAddDeployment()


win32: LIBS += -L$$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw/ -lglfw3

INCLUDEPATH += $$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw
DEPENDPATH += $$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw

win32: LIBS += -L$$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw/ -lglfw3dll

INCLUDEPATH += $$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw
DEPENDPATH += $$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/lib-mingw

INCLUDEPATH += $$PWD/../../../glfw/glfw-3.2.1.bin.WIN32/include/GLFW

HEADERS += \
    ../../../glfw/glfw-3.2.1.bin.WIN32/include/GLFW/glfw3.h \
    ../../../glfw/glfw-3.2.1.bin.WIN32/include/GLFW/glfw3native.h

win32: LIBS += -L$$PWD/../../../Qt/Qt5.3.2/Tools/mingw482_32/i686-w64-mingw32/lib/ -lgdi32

INCLUDEPATH += $$PWD/../../../Qt/Qt5.3.2/Tools/mingw482_32/i686-w64-mingw32/include
DEPENDPATH += $$PWD/../../../Qt/Qt5.3.2/Tools/mingw482_32/i686-w64-mingw32/include
