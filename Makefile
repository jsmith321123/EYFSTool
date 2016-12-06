#############################################################################
# Makefile for building: EYFSTool
# Generated by qmake (2.01a) (Qt 4.8.7) on: Thu Oct 13 16:30:14 2016
# Project:  EYFSTool.pro
# Template: app
# Command: /usr/lib/x86_64-linux-gnu/qt4/bin/qmake -o Makefile EYFSTool.pro
#############################################################################

####### Compiler, tools and options

CC            = gcc
CXX           = g++
DEFINES       = -DQT_NO_DEBUG -DQT_SQL_LIB -DQT_GUI_LIB -DQT_CORE_LIB -DQT_SHARED
CFLAGS        = -m64 -pipe -O2 -Wall -W -D_REENTRANT $(DEFINES)
CXXFLAGS      = -m64 -pipe -O2 -Wall -W -D_REENTRANT -std=c++11 $(DEFINES)
INCPATH       = -I/usr/share/qt4/mkspecs/linux-g++-64 -I. -I/usr/include/qt4/QtCore -I/usr/include/qt4/QtGui -I/usr/include/qt4/QtSql -I/usr/include/qt4 -I. -Iqt_classes -Iqt_classes/Screens -I.
LINK          = g++
LFLAGS        = -m64 -Wl,-O1
LIBS          = $(SUBLIBS)  -L/usr/lib/x86_64-linux-gnu -lQtSql -lQtGui -lQtCore -lpthread 
AR            = ar cqs
RANLIB        = 
QMAKE         = /usr/lib/x86_64-linux-gnu/qt4/bin/qmake
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

SOURCES       = main.cpp \
		qt_classes/LoginScreen.cpp \
		qt_classes/MainWindow.cpp \
		qt_classes/NavigationBar.cpp \
		qt_classes/Screen.cpp \
		qt_classes/Screens/AddChildScreen.cpp \
		qt_classes/Screens/CreateReportContainerScreen.cpp \
		qt_classes/Screens/CreateReportScreen.cpp \
		qt_classes/Screens/CreateUserScreen.cpp \
		qt_classes/Screens/GraphGraphicsScene.cpp \
		qt_classes/Screens/LoadReportScreen.cpp \
		qt_classes/Screens/NewAssessmentScreen.cpp \
		qt_classes/Screens/ViewChildScreen.cpp moc_LoginScreen.cpp \
		moc_MainWindow.cpp \
		moc_NavigationBar.cpp \
		moc_Screen.cpp \
		moc_AddChildScreen.cpp \
		moc_CreateUserScreen.cpp \
		moc_NewAssessmentScreen.cpp \
		moc_ViewChildScreen.cpp
OBJECTS       = main.o \
		LoginScreen.o \
		MainWindow.o \
		NavigationBar.o \
		Screen.o \
		AddChildScreen.o \
		CreateReportContainerScreen.o \
		CreateReportScreen.o \
		CreateUserScreen.o \
		GraphGraphicsScene.o \
		LoadReportScreen.o \
		NewAssessmentScreen.o \
		ViewChildScreen.o \
		moc_LoginScreen.o \
		moc_MainWindow.o \
		moc_NavigationBar.o \
		moc_Screen.o \
		moc_AddChildScreen.o \
		moc_CreateUserScreen.o \
		moc_NewAssessmentScreen.o \
		moc_ViewChildScreen.o
DIST          = /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
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
		EYFSTool.pro
QMAKE_TARGET  = EYFSTool
DESTDIR       = 
TARGET        = EYFSTool

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

all: Makefile $(TARGET)

$(TARGET):  $(OBJECTS)  
	$(LINK) $(LFLAGS) -o $(TARGET) $(OBJECTS) $(OBJCOMP) $(LIBS)

Makefile: EYFSTool.pro  /usr/share/qt4/mkspecs/linux-g++-64/qmake.conf /usr/share/qt4/mkspecs/common/unix.conf \
		/usr/share/qt4/mkspecs/common/linux.conf \
		/usr/share/qt4/mkspecs/common/gcc-base.conf \
		/usr/share/qt4/mkspecs/common/gcc-base-unix.conf \
		/usr/share/qt4/mkspecs/common/g++-base.conf \
		/usr/share/qt4/mkspecs/common/g++-unix.conf \
		/usr/share/qt4/mkspecs/qconfig.pri \
		/usr/share/qt4/mkspecs/features/qt_functions.prf \
		/usr/share/qt4/mkspecs/features/qt_config.prf \
		/usr/share/qt4/mkspecs/features/exclusive_builds.prf \
		/usr/share/qt4/mkspecs/features/default_pre.prf \
		/usr/share/qt4/mkspecs/features/release.prf \
		/usr/share/qt4/mkspecs/features/default_post.prf \
		/usr/share/qt4/mkspecs/features/shared.prf \
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
		/usr/lib/x86_64-linux-gnu/libQtSql.prl \
		/usr/lib/x86_64-linux-gnu/libQtGui.prl \
		/usr/lib/x86_64-linux-gnu/libQtCore.prl
	$(QMAKE) -o Makefile EYFSTool.pro
/usr/share/qt4/mkspecs/common/unix.conf:
/usr/share/qt4/mkspecs/common/linux.conf:
/usr/share/qt4/mkspecs/common/gcc-base.conf:
/usr/share/qt4/mkspecs/common/gcc-base-unix.conf:
/usr/share/qt4/mkspecs/common/g++-base.conf:
/usr/share/qt4/mkspecs/common/g++-unix.conf:
/usr/share/qt4/mkspecs/qconfig.pri:
/usr/share/qt4/mkspecs/features/qt_functions.prf:
/usr/share/qt4/mkspecs/features/qt_config.prf:
/usr/share/qt4/mkspecs/features/exclusive_builds.prf:
/usr/share/qt4/mkspecs/features/default_pre.prf:
/usr/share/qt4/mkspecs/features/release.prf:
/usr/share/qt4/mkspecs/features/default_post.prf:
/usr/share/qt4/mkspecs/features/shared.prf:
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
/usr/lib/x86_64-linux-gnu/libQtSql.prl:
/usr/lib/x86_64-linux-gnu/libQtGui.prl:
/usr/lib/x86_64-linux-gnu/libQtCore.prl:
qmake:  FORCE
	@$(QMAKE) -o Makefile EYFSTool.pro

dist: 
	@$(CHK_DIR_EXISTS) .tmp/EYFSTool1.0.0 || $(MKDIR) .tmp/EYFSTool1.0.0 
	$(COPY_FILE) --parents $(SOURCES) $(DIST) .tmp/EYFSTool1.0.0/ && $(COPY_FILE) --parents Hash.h qt_classes/LoginScreen.h qt_classes/MainWindow.h qt_classes/NavigationBar.h qt_classes/Screen.h qt_classes/Screens/AddChildScreen.h qt_classes/Screens/CreateReportContainerScreen.h qt_classes/Screens/CreateReportScreen.h qt_classes/Screens/CreateUserScreen.h qt_classes/Screens/GraphGraphicsScene.h qt_classes/Screens/LoadReportScreen.h qt_classes/Screens/NewAssessmentScreen.h qt_classes/Screens/ViewChildScreen.h .tmp/EYFSTool1.0.0/ && $(COPY_FILE) --parents main.cpp qt_classes/LoginScreen.cpp qt_classes/MainWindow.cpp qt_classes/NavigationBar.cpp qt_classes/Screen.cpp qt_classes/Screens/AddChildScreen.cpp qt_classes/Screens/CreateReportContainerScreen.cpp qt_classes/Screens/CreateReportScreen.cpp qt_classes/Screens/CreateUserScreen.cpp qt_classes/Screens/GraphGraphicsScene.cpp qt_classes/Screens/LoadReportScreen.cpp qt_classes/Screens/NewAssessmentScreen.cpp qt_classes/Screens/ViewChildScreen.cpp .tmp/EYFSTool1.0.0/ && (cd `dirname .tmp/EYFSTool1.0.0` && $(TAR) EYFSTool1.0.0.tar EYFSTool1.0.0 && $(COMPRESS) EYFSTool1.0.0.tar) && $(MOVE) `dirname .tmp/EYFSTool1.0.0`/EYFSTool1.0.0.tar.gz . && $(DEL_FILE) -r .tmp/EYFSTool1.0.0


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

compiler_moc_header_make_all: moc_LoginScreen.cpp moc_MainWindow.cpp moc_NavigationBar.cpp moc_Screen.cpp moc_AddChildScreen.cpp moc_CreateUserScreen.cpp moc_NewAssessmentScreen.cpp moc_ViewChildScreen.cpp
compiler_moc_header_clean:
	-$(DEL_FILE) moc_LoginScreen.cpp moc_MainWindow.cpp moc_NavigationBar.cpp moc_Screen.cpp moc_AddChildScreen.cpp moc_CreateUserScreen.cpp moc_NewAssessmentScreen.cpp moc_ViewChildScreen.cpp
moc_LoginScreen.cpp: qt_classes/MainWindow.h \
		qt_classes/Screen.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screens/CreateUserScreen.h \
		qt_classes/LoginScreen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/LoginScreen.h -o moc_LoginScreen.cpp

moc_MainWindow.cpp: qt_classes/Screen.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screens/CreateUserScreen.h \
		qt_classes/MainWindow.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/MainWindow.h -o moc_MainWindow.cpp

moc_NavigationBar.cpp: qt_classes/NavigationBar.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/NavigationBar.h -o moc_NavigationBar.cpp

moc_Screen.cpp: qt_classes/Screen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/Screen.h -o moc_Screen.cpp

moc_AddChildScreen.cpp: qt_classes/Screen.h \
		qt_classes/Screens/AddChildScreen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/Screens/AddChildScreen.h -o moc_AddChildScreen.cpp

moc_CreateUserScreen.cpp: qt_classes/Screen.h \
		qt_classes/Screens/CreateUserScreen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/Screens/CreateUserScreen.h -o moc_CreateUserScreen.cpp

moc_NewAssessmentScreen.cpp: qt_classes/Screen.h \
		qt_classes/Screens/NewAssessmentScreen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/Screens/NewAssessmentScreen.h -o moc_NewAssessmentScreen.cpp

moc_ViewChildScreen.cpp: qt_classes/Screen.h \
		qt_classes/Screens/ViewChildScreen.h
	/usr/lib/x86_64-linux-gnu/qt4/bin/moc $(DEFINES) $(INCPATH) qt_classes/Screens/ViewChildScreen.h -o moc_ViewChildScreen.cpp

compiler_rcc_make_all:
compiler_rcc_clean:
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
compiler_clean: compiler_moc_header_clean 

####### Compile

main.o: main.cpp qt_classes/LoginScreen.h \
		qt_classes/MainWindow.h \
		qt_classes/Screen.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screens/CreateUserScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o main.o main.cpp

LoginScreen.o: qt_classes/LoginScreen.cpp qt_classes/LoginScreen.h \
		qt_classes/MainWindow.h \
		qt_classes/Screen.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screens/CreateUserScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LoginScreen.o qt_classes/LoginScreen.cpp

MainWindow.o: qt_classes/MainWindow.cpp qt_classes/MainWindow.h \
		qt_classes/Screen.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screens/CreateUserScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o MainWindow.o qt_classes/MainWindow.cpp

NavigationBar.o: qt_classes/NavigationBar.cpp qt_classes/NavigationBar.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NavigationBar.o qt_classes/NavigationBar.cpp

Screen.o: qt_classes/Screen.cpp qt_classes/Screen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o Screen.o qt_classes/Screen.cpp

AddChildScreen.o: qt_classes/Screens/AddChildScreen.cpp qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o AddChildScreen.o qt_classes/Screens/AddChildScreen.cpp

CreateReportContainerScreen.o: qt_classes/Screens/CreateReportContainerScreen.cpp qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screen.h \
		qt_classes/Screens/CreateReportScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CreateReportContainerScreen.o qt_classes/Screens/CreateReportContainerScreen.cpp

CreateReportScreen.o: qt_classes/Screens/CreateReportScreen.cpp qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CreateReportScreen.o qt_classes/Screens/CreateReportScreen.cpp

CreateUserScreen.o: qt_classes/Screens/CreateUserScreen.cpp qt_classes/Screens/CreateUserScreen.h \
		qt_classes/Screen.h \
		Hash.h \
		qt_classes/MainWindow.h \
		qt_classes/NavigationBar.h \
		qt_classes/Screens/AddChildScreen.h \
		qt_classes/Screens/CreateReportScreen.h \
		qt_classes/Screens/CreateReportContainerScreen.h \
		qt_classes/Screens/LoadReportScreen.h \
		qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screens/ViewChildScreen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o CreateUserScreen.o qt_classes/Screens/CreateUserScreen.cpp

GraphGraphicsScene.o: qt_classes/Screens/GraphGraphicsScene.cpp qt_classes/Screens/GraphGraphicsScene.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o GraphGraphicsScene.o qt_classes/Screens/GraphGraphicsScene.cpp

LoadReportScreen.o: qt_classes/Screens/LoadReportScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o LoadReportScreen.o qt_classes/Screens/LoadReportScreen.cpp

NewAssessmentScreen.o: qt_classes/Screens/NewAssessmentScreen.cpp qt_classes/Screens/NewAssessmentScreen.h \
		qt_classes/Screen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o NewAssessmentScreen.o qt_classes/Screens/NewAssessmentScreen.cpp

ViewChildScreen.o: qt_classes/Screens/ViewChildScreen.cpp qt_classes/Screens/ViewChildScreen.h \
		qt_classes/Screen.h
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o ViewChildScreen.o qt_classes/Screens/ViewChildScreen.cpp

moc_LoginScreen.o: moc_LoginScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_LoginScreen.o moc_LoginScreen.cpp

moc_MainWindow.o: moc_MainWindow.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_MainWindow.o moc_MainWindow.cpp

moc_NavigationBar.o: moc_NavigationBar.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_NavigationBar.o moc_NavigationBar.cpp

moc_Screen.o: moc_Screen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_Screen.o moc_Screen.cpp

moc_AddChildScreen.o: moc_AddChildScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_AddChildScreen.o moc_AddChildScreen.cpp

moc_CreateUserScreen.o: moc_CreateUserScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_CreateUserScreen.o moc_CreateUserScreen.cpp

moc_NewAssessmentScreen.o: moc_NewAssessmentScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_NewAssessmentScreen.o moc_NewAssessmentScreen.cpp

moc_ViewChildScreen.o: moc_ViewChildScreen.cpp 
	$(CXX) -c $(CXXFLAGS) $(INCPATH) -o moc_ViewChildScreen.o moc_ViewChildScreen.cpp

####### Install

install:   FORCE

uninstall:   FORCE

FORCE:

