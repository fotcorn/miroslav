######################################################################
# Automatically generated by qmake (2.01a) Sa 20. Jan 21:40:16 2007
######################################################################

TEMPLATE = app
TARGET = Miroslav
DEPENDPATH += . res src
INCLUDEPATH += .

QT += network

RESOURCES += res/resource.qrc

TRANSLATIONS = i18n/de.ts
 
win32 {
	RC_FILE += .\res\icon.rc
}

# Input
HEADERS += src/chatedit.h \
           src/connectwindow.h \
           src/highlighter.h \
           src/listview.h \
           src/mainwidget.h \
           src/mainwindow.h \
           src/network.h \
           src/trayicon.h \
		   src/settings.h \
		   src/changenickdialog.h
SOURCES += src/chatedit.cpp \
           src/connectwindow.cpp \
           src/highlighter.cpp \
           src/main.cpp \
           src/mainwidget.cpp \
           src/mainwindow.cpp \
           src/network.cpp \
           src/trayicon.cpp \
		   src/settings.cpp \
		   src/changenickdialog.cpp
