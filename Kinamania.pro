#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T01:10:18
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia

TARGET = Kinamania
TEMPLATE = app

QMAKE_CXXFLAGS_DEBUG += -D_DEBUG
#QMAKE_CXXFLAGS_RELEASE += -D_DEBUG

SOURCES +=  main.cpp \
            mainwindow.cpp \
            widget.cpp

HEADERS  += mainwindow.h \
            widget.h

FORMS    += mainwindow.ui

RESOURCES += kinamania.qrc

# Windows Executable Icon
win32:RC_FILE = kinamania.rc

TRANSLATIONS += l10n/kinamania_ru.ts \
                l10n/kinamania_en.ts

OTHER_FILES +=  ReadMe.md \
                ChangeLog.txt \
                Description.txt \
                kinamania.rc
