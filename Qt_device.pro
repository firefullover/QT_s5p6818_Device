#-------------------------------------------------
#
# Project created by QtCreator 2024-08-08T08:59:48
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QT_device
TEMPLATE = app


SOURCES += main.cpp\
        lab.cpp \
    engine.cpp \
    camera.cpp

HEADERS  += lab.h \
    engine.h \
    camera.h

FORMS    += lab.ui
LIBS += -ljpeg

unix:!macx: LIBS += -L$$PWD/../../../../../../root/yjz_wkspace/buildroot/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/ -ljpeg

INCLUDEPATH += $$PWD/../../../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../../../usr/local/include

unix:!macx: PRE_TARGETDEPS += $$PWD/../../../../../../root/yjz_wkspace/buildroot/output/host/usr/arm-buildroot-linux-gnueabi/sysroot/usr/lib/libjpeg.a
