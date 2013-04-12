QT       += core
QT       -= gui

CONFIG   += console
CONFIG   -= app_bundle

CONFIG   += mobility
MOBILITY = contacts

TARGET = exportemplapp
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

COMPPATHS = src qtconsole-ui datasrc-qt engine-hw filesys-cxx
INCLUDEPATH = $$COMPPATHS
DEPENDPATH = $$COMPPATHS
HEADERS += abstract.hpp datasrc_concrete.hpp engine.hpp filesys_concrete.hpp
SOURCES += main.cpp datasrc.cpp datasrc_concrete.cpp engine.cpp filesys_concrete.cpp

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
