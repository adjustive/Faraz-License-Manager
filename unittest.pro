#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T12:35:08
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = unittest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

target.path = /usr/lib
INSTALLS += target
LIBS += -lcryptopp

INCLUDEPATH += $$PWD/shared

LIBS += -L$$PWD/ -lcryptopp
INCLUDEPATH += $$PWD/cryptopp562
DEPENDPATH += $$PWD/cryptopp562
PRE_TARGETDEPS += $$PWD/libcryptopp.a


SOURCES += unittest/main.cpp \
    shared/rsautil.cpp \
    shared/hexutil.cpp

HEADERS += \
    shared/rsautil.h \
    shared/productid.h \
    shared/hexutil.h \
    shared/hardwareuid.h

