#-------------------------------------------------
#
# Project created by QtCreator 2015-05-18T21:58:21
#
#-------------------------------------------------

QT       += core gui

CONFIG += c++11

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TestTask
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    scene.cpp \
    abstractshape.cpp \
    canvas.cpp \
    canvasobserver.cpp \
    shapes/linesegment.cpp \
    shapes/rectangle.cpp \
    shapes/edgerectangle.cpp \
    shapes/ellipse.cpp \
    shapes/triangle.cpp

HEADERS  += mainwindow.h \
    scene.h \
    abstractshape.h \
    canvas.h \
    canvasobserver.h \
    shapes/linesegment.h \
    shapes/rectangle.h \
    shapes/edgerectangle.h \
    shapes/ellipse.h \
    shapes/triangle.h

FORMS    += mainwindow.ui

CONFIG += mobility
MOBILITY = 

