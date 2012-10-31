TEMPLATE = lib
CONFIG += plugin
TARGET = $$qtLibraryTarget(qtgeoservices_offline)

PLUGIN_TYPE=geoservices

include(../common.pri)

QT += sql

CONFIG += mobility
MOBILITY = location

HEADERS += \
            qgeomapreply_sqlite.h \
            qgeomappingmanagerengine_offline.h \
            qgeoserviceproviderplugin_offline.h \
            debug_offline.h


SOURCES += \
            qgeomapreply_sqlite.cpp \
            qgeomappingmanagerengine_offline.cpp \
            qgeoserviceproviderplugin_offline.cpp



RESOURCES = qtgeoservices_offline.qrc

symbian {
    TARGET.EPOCALLOWDLLDATA = 1
    TARGET.CAPABILITY = Location NetworkServices
    #TARGET.UID3 = 0x20045CF8
}

contains(MEEGO_EDITION,harmattan) {
    target.path = /opt/qtgeoservices_offline/lib
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
