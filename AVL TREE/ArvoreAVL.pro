QT += core
QT -= gui

CONFIG += c++11

TARGET = ArvoreAVL
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    treeavl.cpp \
    Game_Physics.cpp

HEADERS += \
    treeavl.h \
    Game_Physics.h
