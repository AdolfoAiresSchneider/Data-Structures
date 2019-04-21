QT += core
QT -= gui

CONFIG += c++11

TARGET = MauMau2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    list.cpp \
    cartas.cpp \
    maumau.cpp

HEADERS += \
    list.h \
    cartas.h \
    maumau.h \
    pilha.h

DISTFILES += \
    ../../build-MauMau2-Desktop_Qt_5_7_0_GCC_64bit-Debug/testes.txt
