#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSound>

#include <QPaintEvent>
#include <QTimerEvent>
#include <QKeyEvent>


class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

private:
    int timerID;
    int msec;

    int score;
    int lives;
    int delay;
    int gotIt;

    int sideState;
    int canState;
    int chiefState;

    bool sound;
    int soundDelay;

    QChar keys[4];
    QString strPause;
    QString strPressKey;
    QString strGameOver;
    QString strWindowTitle;

    enum gameState { // 0 - Main Screen, 1 - Game, 2 - Won, 3 - Game Over, 4 - Pause
        MainScreen,
        TheGame,
        TheWon,
        GameOver,
        Pause
    };

    int currentGameState;

    QSound *s_got;
    QSound *s_move;
    QSound *s_start;
    QSound *s_miss;
    QSound *s_gameOver;

    QPixmap *pixSurface;

    QPixmap pixBackground;
    QPixmap pixChair;
    QPixmap pixWonScreen;

    QPixmap pixCans[8]; // 0-3 - leftside, 4-7 - rightside
    QPixmap pixChiefs[4];
    QPixmap pixBroken[2];
    QPixmap pixDigits[10];

    QPoint chiefCoords[4];
    QPoint chairCoords[3];
    QPoint cansCoords[4][4];
    QPoint hintsCoords[6];
    QPoint brokenCoords[2];
    QPoint digitCoords[4];

private:
    void initAll();

    void initCansCoords();
    void initChairCoords();
    void initChiefCoords();
    void initBrokenCoords();
    void initDigitCoords();

    void initHintsCoords();

    void initStrings();

    void refreshDelay();
    void resetAllVariables();

    void drawGameFrame();
    void drawChairBar(QPainter &painter);

    void drawAll(QPainter &painter);
    void drawKeyHints(QPainter &painter);
    void drawGameText(const int aX, const int aY, const QString &aStr, QPainter &painter);

    void drawDigitPairs(int number, int pair, QPainter &painter);

    void pauseGame(bool aPause);

    void stopAllSfx();

    QPixmap getCanPixmap() const;
    QPoint getCanCoords() const;

protected slots:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

protected slots:
    void slotEnableSound(bool aSound);
    void slotStartNewGame();
    void slotReset();
};

#endif // WIDGET_H
