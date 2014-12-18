#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QSound>

#include <QPaintEvent>
#include <QTimerEvent>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QSettings>

#include <QStringList>

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = 0);
    ~Widget();

public:
    //void setCanvasSize(int aW, int aH, int config);

private:
    QSettings *iniSettings;
    QString iniFileName;

    bool drawRects;

    int canvas_w;
    int canvas_h;

    int screen_w;
    int screen_h;

    bool configAvailable;

    int timerID;
    int msec;

    int score;
    int lives;
    int delay;
    //int gotIt;

    int sideState;
    int canState;
    int chiefState;
    int dendyState;

    int buttonState;

    bool sound;
    int soundDelay;

    int dendyDelay;
    int brokenDelay;
    int brokenState;

    int keysDelay;
    bool keysAvailable;

    bool sfxDirAndFilesAvailable;
    bool gfxDirAndFilesAvailable;

    QString dirName;

    QChar keys[4];
    QString strPause;
    QString strPressKey;
    QString strGameOver;
    QString strWindowTitle;

    QStringList gfxFiles;
    QStringList sfxFiles;

    enum gameState { // 0 - Main Screen, 1 - Game B, 2 - Won, 3 - Game Over, 4 - Pause, 5 - Game A
        MainScreen,
        GameModeB,
        TheWon,
        GameOver,
        Pause,
        GameModeA
    };

    // Game B Mode
    int gbNum[4];
    int gbSideState[4];
    int gbLevel;
    int gbCansState[4];
    int gbInterval;
    bool gbUpdateCoords[4];
    bool gbCanSpawn;
    // End Game B Mode

    int currentGameState;
    int previousGameState;

    QSound *s_got[4];
    QSound *s_move;
    QSound *s_start;
    QSound *s_miss;
    QSound *s_gameOver;
    QSound *s_Win;
    QSound *s_belching;

    QPixmap *pixSurface;

    QPixmap pixBackground;
    QPixmap pixChair;
    QPixmap pixWonScreen;

    QPixmap pixCans[8]; // 0-3 - leftside, 4-7 - rightside
    QPixmap pixChiefs[4];
    QPixmap pixBroken[2];
    QPixmap pixDigits[10];
    QPixmap pixDendy[2];
    QPixmap pixButtons[7];

    QPoint chiefCoords[4];
    QPoint chairCoords[3];
    QPoint cansCoords[4][4];
    QPoint hintsCoords[7];
    QPoint brokenCoords[2];
    QPoint digitCoords[4];
    QPoint dendyCoords[2];
    QPoint buttonCoords[7];

    QRect mouseCoords[7];
    QPoint mouseCoordsAdd[7];
    int buttonCoords_x[7];
    int buttonCoords_y[7];
    int mouseCoordsAdd_x[7];
    int mouseCoordsAdd_y[7];

    int level[7];

private:
    bool checkAllGfxRes();
    QStringList getAllGfxFiles() const;
    QStringList updateGfxListFiles(const QString &dirName);
    void loadAllGfx();

    bool checkAllSfxRes();
    QStringList getAllSfxFiles() const;
    void loadAllSfx();

    bool checkIniFile(const QString &aFileName);

    void initAll();

    void initCansCoords();
    void initChairCoords();
    void initChiefCoords();
    void initBrokenCoords();
    void initDigitCoords();
    void initDendyCoords();
    void initButtonsCoords();

    void initMouseCoords();
    void updateMouserCoords();
    void initMouseCoordsParts();
    int getScaleLevel() const;

    void initLevels();

    void initHintsCoords();

    void initStrings();

    void refreshDelay();
    void resetAllVariables();

    void drawGameFrame();
    void drawChairBar(QPainter &painter);

    void drawAll(QPainter &painter);
    void drawKeyHints(QPainter &painter);
    void drawGameText(const QString &aStr, QPainter &painter);
    void drawButtons(QPainter &painter);

    void drawRectangles(QPainter &painter);

#ifdef _DEBUG
    void writeConfig();
#endif

    void drawDigitPairs(int number, int pair, QPainter &painter);

    void pauseGame(bool aPause);

    void stopAllSfx();

    QPixmap getCanPixmap() const;
    QPoint getCanCoords() const;

signals:
    void disableSound();

protected slots:
    void paintEvent(QPaintEvent *event);
    void timerEvent(QTimerEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

protected slots:
    void slotEnableSound(bool aSound);
    void slotStartNewGameModeA();
    void slotStartNewGameModeB();
    void slotReset();

public slots:
    void slotSetPixmapSize(int w, int h);
};

#endif // WIDGET_H
