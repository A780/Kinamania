#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T01:10:18
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets multimedia
android:QT += androidextras

TARGET = Kinamania
TEMPLATE = app

# Deploy sfx catalog
D_IN = $$PWD/sfx
D_OUT = $$OUT_PWD

win32: {
    CONFIG(debug,debug|release) {
        D_OUT = $$D_OUT/debug
    } else {
        D_OUT = $$D_OUT/release
    }

    D_OUT = $$D_OUT/sfx

    D_IN ~= s,/,\\,g
    D_OUT ~= s,/,\\,g
}

deploy.commands = $(COPY_DIR) $$D_IN $$D_OUT
first.depends = $(first) deploy
export(first.depends)
export(deploy.commands)
QMAKE_EXTRA_TARGETS += first deploy

QMAKE_CXXFLAGS_DEBUG += -D_DEBUG
#QMAKE_CXXFLAGS_RELEASE += -D_DEBUG

SOURCES +=  main.cpp \
            widget.cpp

!android:SOURCES += mainwindow.cpp

HEADERS  += widget.h

!android:HEADERS  += mainwindow.h

!android:FORMS    += mainwindow.ui

RESOURCES += kinamania.qrc

# Windows Executable Icon
win32:RC_FILE = kinamania.rc

TRANSLATIONS += l10n/kinamania_ru.ts \
                l10n/kinamania_en.ts

OTHER_FILES +=  ReadMe.md \
                ChangeLog.txt \
                Description.txt \
                Kinamania_example.ini \
                kinamania.rc

DISTFILES += \
    android/AndroidManifest.xml \
    android/src/hk/ch/kinamania/Kinamania.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
