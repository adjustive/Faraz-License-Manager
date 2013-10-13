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

target.path = /usr/lib
INSTALLS += target
LIBS += -lcryptopp

INCLUDEPATH += $$PWD/shared

LIBS += -L$$PWD/ -lcryptopp
INCLUDEPATH += $$PWD/cryptopp562
DEPENDPATH += $$PWD/cryptopp562
PRE_TARGETDEPS += $$PWD/libcryptopp.a



SOURCES += server/main.cpp \
    shared/rsautil.cpp \
    shared/hexutil.cpp \
    shared/license.cpp \
    server/licenseserver.cpp

HEADERS += \
    shared/rsautil.h \
    shared/productid.h \
    shared/hexutil.h \
    shared/hardwareuid.h \
    shared/license.h \
    shared/cryptopp.h \
    shared/cpuid.h \
    server/licenseserver.h
