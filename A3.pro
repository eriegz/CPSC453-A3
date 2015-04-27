#-------------------------------------------------
#
# Project created by QtCreator 2015-03-31T12:42:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = A3
TEMPLATE = app


SOURCES += main.cpp \
    Sphere.cpp \
    Plane.cpp \
    Triangle.cpp \
    RgbImage.cpp \
    ObjectCreator.cpp \
    Shading.cpp \
    Environment.cpp

HEADERS  += SceneObject.h \
    Sphere.h \
    Plane.h \
    Triangle.h \
    RgbImage.h \
    ObjectCreator.h \
    Shading.h \
    Environment_struct.h \
    Environment.h
