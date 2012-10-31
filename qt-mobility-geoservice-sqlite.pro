TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtgeoservices_sqlite)

PLUGIN_TYPE=geoservices

include(../common.pri)

QT += sql

CONFIG += mobility
MOBILITY = location

HEADERS += \
            qgeomapreply_sqlite.h \
            qgeomappingmanagerengine_sqlite.h \
            qgeoserviceproviderplugin_sqlite.h \
            debug_sqlite.h


SOURCES += \
            qgeomapreply_sqlite.cpp \
            qgeomappingmanagerengine_sqlite.cpp \
            qgeoserviceproviderplugin_sqlite.cpp



RESOURCES = qt-mobility-geoservice-sqlite.qrc

#symbian {
#    TARGET.EPOCALLOWDLLDATA = 1
#    TARGET.CAPABILITY = Location NetworkServices
#    #TARGET.UID3 = 0x20045CF8
#}

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/qtgeoservices_sqlite/lib
    INSTALLS += target
}

OTHER_FILES += \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog \
    qtc_packaging/debian_harmattan/rules \
    qtc_packaging/debian_harmattan/README \
    qtc_packaging/debian_harmattan/manifest.aegis \
    qtc_packaging/debian_harmattan/copyright \
    qtc_packaging/debian_harmattan/control \
    qtc_packaging/debian_harmattan/compat \
    qtc_packaging/debian_harmattan/changelog
