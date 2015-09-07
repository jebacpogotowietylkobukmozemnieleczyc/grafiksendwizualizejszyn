TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1y

SOURCES += main.cpp tga.cpp detailed_cube.cpp \
    bullet.cpp \
    DebugDrawer.cpp \
    GameObject.cpp \
    app.cpp \
    level.cpp
INCLUDEPATH += /usr/include/bullet
LIBS += -lGL -lglut -lGLEW -lBulletDynamics -lBulletCollision -lLinearMath

HEADERS += \
    bullet.hpp \
    DebugDrawer.h \
    GameObject.h \
    app.hpp \
    level.hpp \
    solidsphere.hpp \
    tga.h
