#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

#ifdef _DEBUG
#include <QDebug>
#endif

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
    connect(ui->centralWidget, SIGNAL(disableSound()), this, SLOT(slotDisableSoundMenu()));
    connect(this, SIGNAL(setPixmapSize(int,int)), ui->centralWidget, SLOT(slotSetPixmapSize(int,int)));
    connect(ui->action_Original_screen_size, SIGNAL(triggered()), this, SLOT(slotSetOriginalScreenSize()));

    resize(640, 399 + ui->menuBar->height());
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
    QMessageBox::about(this, tr("About Kinamania"), tr("<p><center><img src=\":/gfx/eyes.jpg\"/></center></p>"
                                                       "<p><strong>Version 0.2</strong></p>"
                                                       "<b>Key controls:</b><br>"
                                                       "* Q, A, P, L or 7, 9, 1, 3 on NumPad - Move;<br>"
                                                       "* F5 - New Game;<br>"
                                                       "* F8 - Reset;<br>"
                                                       "* F10 - Quit;<br>"
                                                       "* Pause or G - Pause.<br><br>"
                                                       "Also, you can use mouse control.<br><br>"
                                                       "Teaser of the Kinamania game is available on <a href=\"http://www.youtube.com/watch?v=0ggWeAdZClc\">YouTube</a>!<br>"
                                                       "Source code is available on <a href=\"https://github.com/A780/Kinamania\">GitHub</a>.<br>"
                                                       "<center><table cellspacing=0 cellpadding=0><tr><td>"
                                                       "<b>Big thanks for Help, /fag!</b><br>"
                                                       "<b>Anonymous artist and A780A</b><br>"
                                                       "<b>December, 2014</b><br>"
                                                       "</td><td><img src=\":/gfx/worm.png\"/></td></tr></table></center>"));
}

void MainWindow::slotDisableSoundMenu()
{
    ui->action_Sound->setChecked(false);
    ui->action_Sound->setEnabled(false);
}

void MainWindow::slotSetOriginalScreenSize()
{
    resize(640, 399 + ui->menuBar->height());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    emit setPixmapSize(event->size().width(), event->size().height() - ui->menuBar->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
