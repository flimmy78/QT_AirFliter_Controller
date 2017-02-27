#-------------------------------------------------
#
# Project created by QtCreator 2016-10-11T14:45:55
#
#-------------------------------------------------

QT       += core gui
QT       += core gui network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
QT += widgets printsupport

TARGET = dabai
TEMPLATE = app


SOURCES += main.cpp\
        dabai.cpp \
    mytcpserver.cpp \
    mytcpclient.cpp \
    iap.cpp \
    qcustomplot.cpp \
    graph.cpp \
    crc.cpp

HEADERS  += dabai.h \
    mytcpserver.h \
    mytcpclient.h \
    myhelper.h \
    iap.h \
    qcustomplot.h \
    graph.h \
    crc.h


FORMS    += dabai.ui

OTHER_FILES += \
   dabai.rc \
   dabai.ico
RC_FILE = dabai.rc
