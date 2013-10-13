#-------------------------------------------------
#
# Project created by QtCreator 2013-10-06T11:36:41
#
#-------------------------------------------------

QT       += core network
QT       -= gui

TARGET = client
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



SOURCES += client/main.cpp \
    shared/rsautil.cpp \
    shared/hexutil.cpp \
    shared/license.cpp \
    client/licenseclient.cpp \
    client/netclient.cpp \
    shared/netobject.cpp

HEADERS += \
    shared/rsautil.h \
    shared/productid.h \
    shared/hexutil.h \
    shared/hardwareuid.h \
    shared/license.h \
    shared/cryptopp.h \
    client/licenseclient.h \
    shared/cpuid.h \
    client/netclient.h \
    shared/netconst.h \
    shared/netobject.h
