TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp tga.cpp detailed_cube.cpp \
    bullet.cpp \
    DebugDrawer.cpp \
    GameObject.cpp
INCLUDEPATH += /usr/include/bullet
LIBS += -lGL -lglut -lGLEW -lBulletDynamics -lBulletCollision -lLinearMath

HEADERS += \
    bullet.hpp \
    DebugDrawer.h \
    GameObject.h
