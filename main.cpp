#include "mainwindow.h"

#include <QApplication>
#include <QTranslator>
#include <QLocale>

#include <ctime>

int main(int argc, char *argv[])
{
    qsrand(time(0)); // Init Randomizer

    QApplication a(argc, argv);

    QTranslator appTranslator;
    appTranslator.load("chervemania_" + QLocale::system().name(), "://l10n/");
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.show();

    return a.exec();
}
