TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CXXFLAGS += -std=c++1y

SOURCES += main.cpp \
    bullet.cpp \
    debugdrawer.cpp \
    gameobject.cpp \
    app.cpp \
    level.cpp
INCLUDEPATH += /usr/include/bullet
LIBS += -lGL -lglut -lGLEW -lSOIL -lBulletDynamics -lBulletCollision -lLinearMath

HEADERS += \
    bullet.hpp \
    debugdrawer.h \
    gameobject.h \
    app.hpp \
    level.hpp \
    solidsphere.hpp \
    SOIL.h
