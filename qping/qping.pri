#QT       += core gui
QT       += network

INCLUDEPATH += $$PWD

HEADERS  += \
        $$PWD/qping.h \
        $$PWD/qpingthread.h

SOURCES += \
        $$PWD/qping.cpp \
        $$PWD/qpingthread.cpp

#FORMS += \
        $$PWD/qping.ui 

#RESOURCES += \
        $$PWD/qping.qrc

#include(./sqlite/sqlite.pri)
