#-------------------------------------------------
#
# Project created by QtCreator 2016-11-29T16:46:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MatrixCalculator
TEMPLATE = app

DEFINES -= DEBUG

SOURCES += main.cpp\
        widget.cpp \
    doublespinboxdelegate.cpp \
    matrix_error.cpp

HEADERS  += widget.h \
    matrix.h \
    doublespinboxdelegate.h \
    matrix_error.h

FORMS    += widget.ui

QMAKE_CXXFLAGS += -std=c++14
