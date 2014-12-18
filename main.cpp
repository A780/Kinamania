#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QFileInfo>
#include <QSettings>

#ifdef Q_OS_ANDROID
#include <QDesktopWidget>
#endif

#include <ctime>

#ifdef _DEBUG
#include <QDebug>
#endif

#ifdef Q_OS_ANDROID
#include "widget.h"
#else
#include "mainwindow.h"
#endif

int main(int argc, char *argv[])
{
    qsrand(time(0)); // Init Randomizer

    QApplication a(argc, argv);

    qApp->setOrganizationDomain("hk");
    qApp->setOrganizationName("CherveThread's Group");
    qApp->setApplicationName("Kinamania");

#ifndef Q_OS_ANDROID
    bool config = true;
    QString fileName = qApp->applicationDirPath() + "/Kinamania.ini";
    QFileInfo fileInfo(fileName);

    if (!fileInfo.exists() && !fileInfo.isFile() && !fileInfo.isReadable()) {
#ifdef _DEBUG
        qDebug() << "Config file" << fileName << "isn't exist!";
#endif
        config = false;
    }
#endif

    QTranslator appTranslator;
    appTranslator.load("kinamania_" + QLocale::system().name(), "://l10n/");
    a.installTranslator(&appTranslator);
#ifdef Q_OS_ANDROID
    Widget w;
    w.slotSetPixmapSize(qApp->desktop()->screenGeometry().width(), qApp->desktop()->screenGeometry().height());
    w.showFullScreen();
#else
    MainWindow w;
    if (!config) {
        w.setCanvasSize(640, 399);
    } else {
        QSettings iniSettings(fileName, QSettings::IniFormat);
        iniSettings.beginGroup("Canvas");
        int canvas_w = iniSettings.value("Width").toInt();
        int canvas_h = iniSettings.value("Height").toInt();
        iniSettings.endGroup();

#ifdef _DEBUG
        qDebug() << "C.Width:" << canvas_w << "C.Height:" << canvas_h;
#endif

        w.setCanvasSize(canvas_w, canvas_h);
    }
    w.show();
#endif

    return a.exec();
}
