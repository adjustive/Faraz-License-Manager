#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T11:36:41
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = client
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += client/main.cpp \
    shared/rsautil.cpp \
    shared/hexutil.cpp

HEADERS += \
    shared/rsautil.h \
    shared/productid.h \
    shared/hexutil.h \
    shared/hardwareuid.h
