include(src/current_config.pri)

# qmake could be used to handle plain C++ also,
# but we shall keep things simple.
!WITH_QT {
  error("qmake not supported for non-Qt configurations")
}

QT       += core

!WITH_GUI {
  QT -= gui
}

# setting for qDebug() (affects Win32 only)
CONFIG   += console

# whether to bundle executable (affects Mac OS X only)
CONFIG   -= app_bundle

LUA_LINK_AS_PKG_CONFIG {
  CONFIG += link_pkgconfig
  PKGCONFIG += lua5.1
}

WITH_QT_MOBILITY {
  CONFIG   += mobility
  MOBILITY = contacts
}

TARGET = exportemplapp
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

INCLUDEPATH = $$SRCDIRS
DEPENDPATH = $$SRCDIRS

DEFINES += QT_NO_CAST_FROM_ASCII QT_NO_CAST_TO_ASCII

include(src/source_list.pri)

LUA_LINK_AS_SOURCE_CODE {
  INCLUDEPATH += lua-5.2.2/src
  DEPENDPATH += lua-5.2.2/src
  SOURCES += lapi.c lauxlib.c lbaselib.c lbitlib.c lcode.c lcorolib.c lctype.c ldblib.c ldebug.c ldo.cpp ldump.c lfunc.c lgc.c linit.c liolib.c llex.c lmathlib.c lmem.c loadlib.c lobject.c lopcodes.c loslib.c lparser.c lstate.c lstring.c lstrlib.c ltable.c ltablib.c ltm.c lundump.c lvm.c lzio.c
}

IS_HARMATTAN {
  OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
}

contains(MEEGO_EDITION,harmattan) {
  target.path = /opt/exportemplapp/bin
  INSTALLS += target

  scripts.files = $$PWD/lua-src/*.lua
  scripts.path = /opt/exportemplapp/scripts
  INSTALLS += scripts
}
