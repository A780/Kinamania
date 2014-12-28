#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QResizeEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public:
    void setCanvasSize(int aWidth, int aHeight);

private:
    int canvas_w;
    int canvas_h;

protected:
    void changeEvent(QEvent *e);

protected slots:
    void slotDisableSoundMenu();
    void slotSetOriginalScreenSize();

protected slots:
    void resizeEvent(QResizeEvent *event);

signals:
    void setPixmapSize(int, int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
