TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt
CONFIG += c++11

SOURCES += main.cpp \
    directorymonitor.cpp \
    fileassociation.cpp

LIBS += -lboost_system -lboost_filesystem -lboost_program_options

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    directorymonitor.h \
    fileassociation.h

