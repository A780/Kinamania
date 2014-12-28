#include "mainwindow.h"
#include "ui_mainwindow.h"

#ifdef _DEBUG
#include <QDebug>
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionAbout_Qt, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(ui->action_About, SIGNAL(triggered()), ui->centralWidget, SLOT(slotShowAbout()));
    connect(ui->actionGame_Mode_A, SIGNAL(triggered()), ui->centralWidget, SLOT(slotStartNewGameModeA()));
    connect(ui->actionGame_Mode_B, SIGNAL(triggered()), ui->centralWidget, SLOT(slotStartNewGameModeB()));
    connect(ui->action_Reset, SIGNAL(triggered()), ui->centralWidget, SLOT(slotReset()));
    connect(ui->action_Sound, SIGNAL(triggered(bool)), ui->centralWidget, SLOT(slotEnableSound(bool)));
    connect(ui->centralWidget, SIGNAL(disableSound()), this, SLOT(slotDisableSoundMenu()));
    connect(this, SIGNAL(setPixmapSize(int,int)), ui->centralWidget, SLOT(slotSetPixmapSize(int,int)));
    connect(ui->action_Original_screen_size, SIGNAL(triggered()), this, SLOT(slotSetOriginalScreenSize()));

    //resize(640, 399 + ui->menuBar->height());
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

void MainWindow::slotDisableSoundMenu()
{
    ui->action_Sound->setChecked(false);
    ui->action_Sound->setEnabled(false);
}

void MainWindow::setCanvasSize(int aWidth, int aHeight)
{
    canvas_w = aWidth;
    canvas_h = aHeight;

    resize(canvas_w, canvas_h + ui->menuBar->height());
    //ui->centralWidget->setCanvasSize(canvas_w, canvas_h, aConfigAvailable);
}

void MainWindow::slotSetOriginalScreenSize()
{
    resize(canvas_w, canvas_h + ui->menuBar->height());
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    emit setPixmapSize(event->size().width(), event->size().height() - ui->menuBar->height());
}

MainWindow::~MainWindow()
{
    delete ui;
}
