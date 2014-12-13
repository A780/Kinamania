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

protected:
    void changeEvent(QEvent *e);

protected slots:
    void slotShowAbout();
    void slotDisableSoundMenu();

protected slots:
    void resizeEvent(QResizeEvent *event);

signals:
    void setPixmapSize(int, int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
