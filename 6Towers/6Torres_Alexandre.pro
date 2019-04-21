QT += core
QT -= gui

CONFIG += c++11

TARGET = 6Torres_Alexandre
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    myqueue.cpp \
    Ficha.cpp

HEADERS += \
    pilha.h \
    myqueue.h \
    Ficha.h
