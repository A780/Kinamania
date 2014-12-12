#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About, SIGNAL(triggered()), this, SLOT(slotShowAbout()));
    connect(ui->action_New_Game, SIGNAL(triggered()), ui->centralWidget, SLOT(slotStartNewGame()));
    connect(ui->action_Reset, SIGNAL(triggered()), ui->centralWidget, SLOT(slotReset()));
    connect(ui->action_Sound, SIGNAL(triggered(bool)), ui->centralWidget, SLOT(slotEnableSound(bool)));
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::slotShowAbout()
{
    QMessageBox::about(this, tr("About CherveMania"), tr("<p><strong>Version 0.1</strong></p>"
                                                         "Keys: <br>"
                                                         " Q, A, P, L or 7, 9, 1, 3 on NumPad - Move;<br>"
                                                         " F5 - New Game;<br>"
                                                         " F8 - Reset;<br>"
                                                         " F10 - Quit;<br>"
                                                         " Pause or G - Pause;<br><br>"
                                                         "Source code is available on <a href=\"https://github.com/A780/CherveMania\">GitHub</a>.<br>"
                                                         "<p><center><b>Big thanks for Help, /fag!</b></center></p>"
                                                         "<p><center><b>Anonymous artist and A780A, December 2014</b></center></p>"));
}

MainWindow::~MainWindow()
{
    delete ui;
}
