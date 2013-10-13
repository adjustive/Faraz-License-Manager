#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T11:37:10
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += server/main.cpp \
    shared/rsautil.cpp \
    shared/hexutil.cpp \
    server/license.cpp

HEADERS += \
    shared/rsautil.h \
    shared/productid.h \
    shared/hexutil.h \
    shared/hardwareuid.h \
    server/license.h
