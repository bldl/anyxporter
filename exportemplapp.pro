QT       += core
QT       -= gui

TARGET = exportemplapp
CONFIG   += console
CONFIG   -= app_bundle
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

COMPPATHS = src qtconsole-ui datasrc-dummy engine-hw filesys-cxx
INCLUDEPATH = $$COMPPATHS
DEPENDPATH = $$COMPPATHS
HEADERS += abstract.hpp datasrc_concrete.hpp engine.hpp filesys_concrete.hpp
SOURCES += main.cpp datasrc.cpp datasrc_concrete.cpp engine.cpp filesys_concrete.cpp
