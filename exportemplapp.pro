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

WITH_QT_MOBILITY {
  CONFIG   += mobility
  MOBILITY = contacts
}

TARGET = exportemplapp
QMAKE_CXXFLAGS += -std=c++0x

TEMPLATE = app

INCLUDEPATH = $$SRCDIRS
DEPENDPATH = $$SRCDIRS

include(src/source_list.pri)

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
