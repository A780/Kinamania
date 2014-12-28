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
    android/res/values/libs.xml \
    android/build.gradle \
    android/src/org/qtproject/qt5/android/bindings/QtActivity.java \
    android/src/hk/ch/kinamania/Vibro.java

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android
