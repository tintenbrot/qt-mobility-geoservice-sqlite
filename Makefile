#############################################################################
# Makefile for building: libqtgeoservices_sqlite.so
# Generated by qmake (2.01a) (Qt 4.8.1) on: Thu Nov 1 05:34:53 2012
# Project:  qt-mobility-geoservice-sqlite.pro
# Template: lib
# Command: /usr/bin/qmake-qt4 -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile qt-mobility-geoservice-sqlite.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_WEBKIT -DQT_NO_DEBUG -DQT_PLUGIN -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
CXXFLAGS      = -pipe -O2 -Wall -W -D_REENTRANT -fPIC $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++ -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtSql -I/usr/include/qt4 -I/usr/include/QtLocation -I. -I.. -I/usr/include -I/usr/include/QtMobility -I.
LINK          = g++
LFLAGS        = -Wl,-O1 -shared
LIBS          = $(SUBLIBS)  -L/usr/lib/i386-linux-gnu -L/usr/lib -lQtLocation -lQtSql -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/bin/qmake-qt4
TAR           = tar -cf
COMPRESS      = gzip -9f
COPY          = cp -f
SED           = sed
COPY_FILE     = $(COPY)
COPY_DIR      = $(COPY) -r
STRIP         = strip
INSTALL_FILE  = install -m 644 -p
INSTALL_DIR   = $(COPY_DIR)
INSTALL_PROGRAM = install -m 755 -p
DEL_FILE      = rm -f
SYMLINK       = ln -f -s
DEL_DIR       = rmdir
MOVE          = mv -f
CHK_DIR_EXISTS= test -d
MKDIR         = mkdir -p

####### Output directory

OBJECTS_DIR   = ./

####### Files

SOURCES       = qgeomapreply_sqlite.cpp \
		qgeomappingmanagerengine_sqlite.cpp \
		qgeoserviceproviderplugin_sqlite.cpp moc_qgeomapreply_sqlite.cpp \
		moc_qgeomappingmanagerengine_sqlite.cpp \
		moc_qgeoserviceproviderplugin_sqlite.cpp \
		qrc_qt-mobility-geoservice-sqlite.cpp
OBJECTS       = qgeomapreply_sqlite.o \
		qgeomappingmanagerengine_sqlite.o \
		qgeoserviceproviderplugin_sqlite.o \
		moc_qgeomapreply_sqlite.o \
		moc_qgeomappingmanagerengine_sqlite.o \
		moc_qgeoserviceproviderplugin_sqlite.o \
		qrc_qt-mobility-geoservice-sqlite.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		../../../common.pri \
		../common.pri \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/mobility.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		qt-mobility-geoservice-sqlite.pro
QMAKE_TARGET  = qtgeoservices_sqlite
DESTDIR       = ../
TARGET        = libqtgeoservices_sqlite.so
TARGETD       = libqtgeoservices_sqlite.so

first: all
####### Implicit rules

.SUFFIXES: .o .c .cpp .cc .cxx .C

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cc.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.C.o:
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o "$@" "$<"

.c.o:
	$(CC) -c $(CFLAGS) $(INCPATH) -o "$@" "$<"

####### Build rules

all: Makefile  ../$(TARGET)

../$(TARGET):  $(OBJECTS) $(SUBLIBS) $(OBJCOMP)  
	@$(CHK_DIR_EXISTS) ../ || $(MKDIR) ../ 
	-$(DEL_FILE) $(TARGET)
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS) $(OBJCOMP)
	-$(MOVE) $(TARGET) ../



Makefile: qt-mobility-geoservice-sqlite.pro  /usr/share/qt4/mkspecs/linux-g++/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		../../../common.pri \
		../common.pri \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/mobility.prf \
		/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf \
		/usr/share/qt4/mkspecs/features/warn_on.prf \
		/usr/share/qt4/mkspecs/features/qt.prf \
		/usr/share/qt4/mkspecs/features/unix/thread.prf \
		/usr/share/qt4/mkspecs/features/moc.prf \
		/usr/share/qt4/mkspecs/features/resources.prf \
		/usr/share/qt4/mkspecs/features/uic.prf \
		/usr/share/qt4/mkspecs/features/yacc.prf \
		/usr/share/qt4/mkspecs/features/lex.prf \
		/usr/share/qt4/mkspecs/features/include_source_dir.prf \
		/usr/lib/libQtLocation.prl \
		/usr/lib/i386-linux-gnu/libQtSql.prl \
		/usr/lib/i386-linux-gnu/libQtGui.prl \
		/usr/lib/i386-linux-gnu/libQtCore.prl
	$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile qt-mobility-geoservice-sqlite.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/modules/qt_webkit_version.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
../../../common.pri:
../common.pri:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/mobility.prf:
/usr/share/qt4/mkspecs/features/unix/gdb_dwarf_index.prf:
/usr/share/qt4/mkspecs/features/warn_on.prf:
/usr/share/qt4/mkspecs/features/qt.prf:
/usr/share/qt4/mkspecs/features/unix/thread.prf:
/usr/share/qt4/mkspecs/features/moc.prf:
/usr/share/qt4/mkspecs/features/resources.prf:
/usr/share/qt4/mkspecs/features/uic.prf:
/usr/share/qt4/mkspecs/features/yacc.prf:
/usr/share/qt4/mkspecs/features/lex.prf:
/usr/share/qt4/mkspecs/features/include_source_dir.prf:
/usr/lib/libQtLocation.prl:
/usr/lib/i386-linux-gnu/libQtSql.prl:
/usr/lib/i386-linux-gnu/libQtGui.prl:
/usr/lib/i386-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -spec /usr/share/qt4/mkspecs/linux-g++ -o Makefile qt-mobility-geoservice-sqlite.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/qtgeoservices_sqlite1.0.0 || $(MKDIR) .tmp/qtgeoservices_sqlite1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/qtgeoservices_sqlite1.0.0/ && $(COPY_FILE) --parents qgeomapreply_sqlite.h qgeomappingmanagerengine_sqlite.h qgeoserviceproviderplugin_sqlite.h debug_sqlite.h .tmp/qtgeoservices_sqlite1.0.0/ && $(COPY_FILE) --parents qt-mobility-geoservice-sqlite.qrc .tmp/qtgeoservices_sqlite1.0.0/ && $(COPY_FILE) --parents qgeomapreply_sqlite.cpp qgeomappingmanagerengine_sqlite.cpp qgeoserviceproviderplugin_sqlite.cpp .tmp/qtgeoservices_sqlite1.0.0/ && (cd `dirname .tmp/qtgeoservices_sqlite1.0.0` && $(TAR) qtgeoservices_sqlite1.0.0.tar qtgeoservices_sqlite1.0.0 && $(COMPRESS) qtgeoservices_sqlite1.0.0.tar) && $(MOVE) `dirname .tmp/qtgeoservices_sqlite1.0.0`/qtgeoservices_sqlite1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/qtgeoservices_sqlite1.0.0


clean:compiler_clean 
	-$(DEL_FILE) $(OBJECTS)
	-$(DEL_FILE) *~ core *.core


####### Sub-libraries

distclean: clean
	-$(DEL_FILE) $(TARGET) 
	-$(DEL_FILE) Makefile


check: first

mocclean: compiler_moc_header_clean compiler_moc_source_clean

mocables: compiler_moc_header_make_all compiler_moc_source_make_all

compiler_moc_header_make_all: moc_qgeomapreply_sqlite.cpp moc_qgeomappingmanagerengine_sqlite.cpp moc_qgeoserviceproviderplugin_sqlite.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_qgeomapreply_sqlite.cpp moc_qgeomappingmanagerengine_sqlite.cpp moc_qgeoserviceproviderplugin_sqlite.cpp
moc_qgeomapreply_sqlite.cpp: qgeomapreply_sqlite.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) qgeomapreply_sqlite.h -o moc_qgeomapreply_sqlite.cpp

moc_qgeomappingmanagerengine_sqlite.cpp: qgeoserviceproviderplugin_sqlite.h \
		qgeomappingmanagerengine_sqlite.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) qgeomappingmanagerengine_sqlite.h -o moc_qgeomappingmanagerengine_sqlite.cpp

moc_qgeoserviceproviderplugin_sqlite.cpp: qgeoserviceproviderplugin_sqlite.h
	/usr/bin/moc-qt4 $(DEFINES) $(INCPATH) qgeoserviceproviderplugin_sqlite.h -o moc_qgeoserviceproviderplugin_sqlite.cpp

compiler_rcc_make_all: qrc_qt-mobility-geoservice-sqlite.cpp
compiler_rcc_clean:
	-$(DEL_FILE) qrc_qt-mobility-geoservice-sqlite.cpp
qrc_qt-mobility-geoservice-sqlite.cpp: qt-mobility-geoservice-sqlite.qrc \
		resources/tile_notavailable.png \
		resources/tile_working.png
	/usr/bin/rcc -name qt-mobility-geoservice-sqlite qt-mobility-geoservice-sqlite.qrc -o qrc_qt-mobility-geoservice-sqlite.cpp

compiler_image_collection_make_all: qmake_image_collection.cpp
compiler_image_collection_clean:
	-$(DEL_FILE) qmake_image_collection.cpp
compiler_moc_source_make_all:
compiler_moc_source_clean:
compiler_uic_make_all:
compiler_uic_clean:
compiler_yacc_decl_make_all:
compiler_yacc_decl_clean:
compiler_yacc_impl_make_all:
compiler_yacc_impl_clean:
compiler_lex_make_all:
compiler_lex_clean:
compiler_clean: compiler_moc_header_clean compiler_rcc_clean 

####### Compile

qgeomapreply_sqlite.o: qgeomapreply_sqlite.cpp qgeomapreply_sqlite.h \
		debug_sqlite.h \
		qgeomappingmanagerengine_sqlite.h \
		qgeoserviceproviderplugin_sqlite.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qgeomapreply_sqlite.o qgeomapreply_sqlite.cpp

qgeomappingmanagerengine_sqlite.o: qgeomappingmanagerengine_sqlite.cpp qgeomappingmanagerengine_sqlite.h \
		qgeoserviceproviderplugin_sqlite.h \
		qgeomapreply_sqlite.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qgeomappingmanagerengine_sqlite.o qgeomappingmanagerengine_sqlite.cpp

qgeoserviceproviderplugin_sqlite.o: qgeoserviceproviderplugin_sqlite.cpp qgeoserviceproviderplugin_sqlite.h \
		qgeomappingmanagerengine_sqlite.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qgeoserviceproviderplugin_sqlite.o qgeoserviceproviderplugin_sqlite.cpp

moc_qgeomapreply_sqlite.o: moc_qgeomapreply_sqlite.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qgeomapreply_sqlite.o moc_qgeomapreply_sqlite.cpp

moc_qgeomappingmanagerengine_sqlite.o: moc_qgeomappingmanagerengine_sqlite.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qgeomappingmanagerengine_sqlite.o moc_qgeomappingmanagerengine_sqlite.cpp

moc_qgeoserviceproviderplugin_sqlite.o: moc_qgeoserviceproviderplugin_sqlite.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_qgeoserviceproviderplugin_sqlite.o moc_qgeoserviceproviderplugin_sqlite.cpp

qrc_qt-mobility-geoservice-sqlite.o: qrc_qt-mobility-geoservice-sqlite.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o qrc_qt-mobility-geoservice-sqlite.o qrc_qt-mobility-geoservice-sqlite.cpp

####### Install

install_target: first FORCE
	@$(CHK_DIR_EXISTS) $(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/ || $(MKDIR) $(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/ 
	-$(INSTALL_PROGRAM) "../$(TARGET)" "$(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/$(TARGET)"
	-$(STRIP) --strip-unneeded "$(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/$(TARGET)"

uninstall_target:  FORCE
	-$(DEL_FILE) "$(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/$(TARGET)"
	-$(DEL_DIR) $(INSTALL_ROOT)/opt/cacheme-full/lib/plugins/geoservices/ 


install:  install_target  FORCE

uninstall: uninstall_target   FORCE

FORCE:

