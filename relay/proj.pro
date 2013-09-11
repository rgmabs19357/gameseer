 #-------------------------------------------------
#
# Project created by QtCreator 2013-01-09T11:51:51
#
#-------------------------------------------------

QT  += core gui xml  widgets


CONFIG += c++11				


TARGET = relay
TEMPLATE = app


SOURCES += main.cpp\
configmgr.cpp \
mainwindow.cpp \
TcpNet.cpp \
TestNet.cpp \
timerwnd.cpp \
deviceswnd.cpp

HEADERS  +=  \
configmgr.h \
mainwindow.h \
TcpNet.h \
TestNet.h \
timerwnd.h \
deviceswnd.h

FORMS    += \
mainwindow.ui \
deviceswnd.ui \
TestNet.ui \
timerwnd.ui \

include($$PWD/../3rdParty/inc/log4qt/log4qt.pri) 

LIBS += -lws2_32
win32:CONFIG(release, debug|release): LIBS += -L$$PWD/lib/ -lQtSolutions_SingleApplication-head
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/lib/ -lQtSolutions_SingleApplication-headd

DEFINES +=	_WIN32_WINNT=0x0501 \
_CRT_SECURE_NO_DEPRECATE \
BOOST_DATE_TIME_NO_LIB BOOST_REGEX_NO_LIB BOOST_ALL_NO_LIB=1


INCLUDEPATH += $$PWD/inc
INCLUDEPATH += $$PWD/../3rdParty/inc
INCLUDEPATH += $$PWD
DEPENDPATH += $$PWD/inc




Release:DESTDIR = release
Release:OBJECTS_DIR = release/.obj
Release:MOC_DIR = release/.moc
Release:RCC_DIR = release/.rcc
Release:UI_DIR = release/.ui

Debug:DESTDIR = debug
Debug:OBJECTS_DIR = debug/.obj
Debug:MOC_DIR = debug/.moc
Debug:RCC_DIR = debug/.rcc
Debug:UI_DIR = debug/.ui