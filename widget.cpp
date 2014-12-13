#include "widget.h"

#include <QPainter>

#ifdef _DEBUG
#include <QDebug>
#endif

//const int coords[][] = ;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    // TODO:
    int screen_w = 640;
    int screen_h = 399;

    initAll();

    resetAllVariables();

    sound = true;
    soundDelay = 75;

    keysDelay = 150;
    keysAvailable = false;

    currentGameState = MainScreen;

    pixBackground.load(":/gfx/background.png"); // Load background

    for (int i = 0; i < 8; ++i) { // 8 is count of frames of cans
        pixCans[i].load(QString(":/gfx/can_%1.png").arg(i));
    }

    for (int i = 0; i < 4; ++i) { // 4 state of chief
        pixChiefs[i].load(QString(":/gfx/chief_%1.png").arg(i));
    }

    for (int i = 0; i < 2; ++i) { // 2 state of broken pepsi can
        pixBroken[i].load(QString(":/gfx/broken_%1.png").arg(i));
    }

    for (int i = 0; i < 10; ++i) { // 10 LCD digits
        pixDigits[i].load(QString(":/gfx/digit_%1.png").arg(i));
    }

    pixChair.load("://gfx/chair.png"); // Load chair

    pixWonScreen.load("://gfx/bsod.png"); // Load won screen

    pixSurface = new QPixmap(screen_w, screen_h);

    s_got = new QSound("sfx/Got.wav", this);
    s_move = new QSound("sfx/Move.wav", this);
    s_start = new QSound("sfx/Start.wav", this);
    s_miss = new QSound("sfx/Miss.wav", this);
    s_gameOver = new QSound("sfx/Gameover.wav", this);

    timerID = startTimer(10);

    setFocusPolicy(Qt::StrongFocus); // For Keys!

    setFixedSize(screen_w, screen_h);
    //setWindowIcon();
    //setWindowTitle(strWindowTitle);
}

void Widget::initAll()
{
    initCansCoords();
    initChiefCoords();
    initChairCoords();
    initBrokenCoords();
    initDigitCoords();

    initHintsCoords();

    initStrings();
}

void Widget::initCansCoords()
{
    cansCoords[0][0] = QPoint(157, 139);
    cansCoords[0][1] = QPoint(177, 145);
    cansCoords[0][2] = QPoint(201, 163);
    cansCoords[0][3] = QPoint(227, 181);

    cansCoords[1][0] = QPoint(469, 139);
    cansCoords[1][1] = QPoint(435, 146);
    cansCoords[1][2] = QPoint(414, 163);
    cansCoords[1][3] = QPoint(390, 181);

    cansCoords[2][0] = QPoint(157, 223);
    cansCoords[2][1] = QPoint(178, 229);
    cansCoords[2][2] = QPoint(201, 248);
    cansCoords[2][3] = QPoint(227, 265);

    cansCoords[3][0] = QPoint(469, 224);
    cansCoords[3][1] = QPoint(435, 231);
    cansCoords[3][2] = QPoint(413, 248);
    cansCoords[3][3] = QPoint(390, 266);
}

void Widget::initChairCoords()
{
    chairCoords[0] = QPoint(398, 121);
    chairCoords[1] = QPoint(384, 121);
    chairCoords[2] = QPoint(369, 121);
}

void Widget::initChiefCoords()
{
    chiefCoords[0] = QPoint(252, 151);
    chiefCoords[1] = QPoint(318, 151);
    chiefCoords[2] = QPoint(250, 226);
    chiefCoords[3] = QPoint(326, 227);
}

void Widget::initBrokenCoords()
{
    brokenCoords[0] = QPoint(219, 286);
    brokenCoords[1] = QPoint(382, 286);
}

void Widget::initDigitCoords()
{
    digitCoords[0] = QPoint(330, 86);
    digitCoords[1] = QPoint(351, 86);
    digitCoords[2] = QPoint(383, 86);
    digitCoords[3] = QPoint(404, 86);
}

void Widget::initHintsCoords()
{
    hintsCoords[0] = QPoint(62, 288);
    hintsCoords[1] = QPoint(62, 351);
    hintsCoords[2] = QPoint(554, 288);
    hintsCoords[3] = QPoint(554, 351);
    hintsCoords[4] = QPoint(554, 135);
    hintsCoords[5] = QPoint(175, 34);
}

void Widget::initStrings()
{
    keys[0] = 'Q';
    keys[1] = 'A';
    keys[2] = 'P';
    keys[3] = 'L';

    strPause = tr("Pause");
    strPressKey = tr("Press any key for start game!");
    strGameOver = tr("Game over!");

    strWindowTitle = tr("CherveMania - The Game");
}

void Widget::refreshDelay()
{
    if (score >= 0 && score < 10) {
        delay = 100;
    }

    if (score >= 10 && score < 15) {
        delay = 50;
    }

    if (score >= 15 && score < 25) {
        delay = 30;
    }

    if (score >= 25 && score < 50) {
        delay = 20;
    }

    if (score >= 50 && score < 75) {
        delay = 18;
    }

    if (score >= 75 && score < 95) {
        delay = 15;
    }

    if (score >= 95 && score < 100) {
        delay = 10;
    }
}

void Widget::resetAllVariables()
{

    msec = sideState = 0;
    canState = (-1);
    chiefState = 0;
//    score = 98;
    score = 0;
//    lives = 0;
    lives = 3;
    delay = 100;
    gotIt = 0;
}

void Widget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    painter.drawPixmap(0, 0, *pixSurface);
}

void Widget::timerEvent(QTimerEvent */*event*/)
{
    int num = qrand() % 16;
    ++msec;

    if (msec == keysDelay && (currentGameState == GameOver || currentGameState == TheWon)) {
        keysAvailable = true;
    }

    if (msec == soundDelay && currentGameState == MainScreen) {
        if (sound && s_start->isFinished()) {
            s_start->play();
        }
    }

    if (msec == soundDelay && currentGameState == GameOver) { // Fix bug with laggy playing this sound
        //for (int i = 0; i < 50; ++i) {
            stopAllSfx();
        //}
        if (sound && s_gameOver->isFinished()) {
#ifdef _DEBUG
            qDebug() << "############### Is playing?";
#endif
            s_gameOver->play();
        }
    }

    if (msec >= delay && currentGameState == TheGame) { // 100 is one sec
        msec = 0;

        if (canState == (-1)) {

            if (num >= 0 && num < 4) {
                sideState = 0;
            }

            if (num >= 4 && num < 8) {
                sideState = 1;
            }

            if (num >= 8 && num < 12) {
                sideState = 2;
            }

            if (num >= 12 && num < 16) {
                sideState = 3;
            }
        }

        ++canState;

        if (canState == 4 && sideState == chiefState) {
            ++score;
            if (sound && s_got->isFinished()) {
                s_got->play();
            }
#ifdef _DEBUG
            qDebug() << "You won! Can is:" << score;
#endif
        } else if (canState == 4 && sideState != chiefState) {
            --lives;
            if (sound && s_miss->isFinished()) {
                s_miss->play();
            }
#ifdef _DEBUG
            qDebug() << "You Lose! Lives:" << lives;
#endif
            if (lives < 0) {
                currentGameState = GameOver;
                resetAllVariables();
            }
        } else {
            if (sound && s_move->isFinished()) {
                s_move->play();
            }
        }

        if (canState >= 4) {
            canState = (-1);
            gotIt = 1;
        }

        if (score >= 100) {
            currentGameState = TheWon;
            resetAllVariables();
        }

#ifdef _DEBUG
        qDebug() << canState << sideState << chiefState << delay;
#endif

        refreshDelay();
    }

    drawGameFrame();
    update();
}

void Widget::keyPressEvent(QKeyEvent *event)
{
#ifdef _DEBUG
    qDebug() << "Key Pressed:" << event->key();
#endif

    if (currentGameState == MainScreen) {
        currentGameState = TheGame;
    }

    bool state = keysAvailable && (currentGameState == GameOver || currentGameState == TheWon);

    if (state) {
        keysAvailable = false;
        currentGameState = TheGame;
    }

    gotIt = 0;

    switch (event->key()) {
    case Qt::Key_Q:
    case Qt::Key_7: {
        chiefState = 0;
        break;
    }
    case Qt::Key_P:
    case Qt::Key_9: {
        chiefState = 1;
        break;
    }
    case Qt::Key_A:
    case Qt::Key_1: {
        chiefState = 2;
        break;
    }
    case Qt::Key_L:
    case Qt::Key_3: {
        chiefState = 3;
        break;
    }
    case Qt::Key_Pause:
    case Qt::Key_G: {
        if (!state) {
            pauseGame(currentGameState != Pause);
        }
        break;
    }
    default:
        break;
    }
}

void Widget::keyReleaseEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Q:
    case Qt::Key_7:
    case Qt::Key_P:
    case Qt::Key_9:
    case Qt::Key_A:
    case Qt::Key_1:
    case Qt::Key_L:
    case Qt::Key_3: {
        //chiefState = (-1);
        break;
    }
        break;
    default:
        break;
    }
}

void Widget::slotEnableSound(bool aSound)
{
    sound = aSound;
}

void Widget::slotStartNewGame()
{
    resetAllVariables();
    currentGameState = TheGame;
}

void Widget::slotReset()
{
    resetAllVariables();
    currentGameState = MainScreen;
}

void Widget::drawGameFrame()
{
    pixSurface->fill(Qt::transparent);

    QPainter painter(pixSurface);

    // Draw background
    painter.drawPixmap(0, 0, pixBackground);

    switch (currentGameState) {
    case MainScreen: {
        drawAll(painter);
        drawKeyHints(painter);
        break;
    }
    case TheGame: {
        // Draw pepsi cans
        if (canState != (-1)) {
            painter.drawPixmap(getCanCoords(), getCanPixmap());
        } else if (gotIt && sideState != chiefState) {
            painter.drawPixmap((sideState % 2 == 0) ? brokenCoords[0] : brokenCoords[1],
                    (sideState % 2 == 0) ? pixBroken[0] : pixBroken[1]);
        }

        // Draw chief
        if (chiefState != (-1)) {
            painter.drawPixmap(chiefCoords[chiefState], pixChiefs[chiefState]);
        }

        // Draw chairbar
        drawChairBar(painter);

        // Draw 90 + score
        drawDigitPairs(90, 0, painter);
        drawDigitPairs(score, 1, painter);
        break;
    }
    case TheWon: {
        painter.drawPixmap(0, 0, pixWonScreen);
        break;
    }
    case GameOver: {
        drawAll(painter);
        drawGameText(255, 34, strGameOver, painter);
        break;
    }
    case Pause: {
        drawGameText(280, 34, strPause, painter);
        break;
    }
    default:
        break;
    }
}

void Widget::drawChairBar(QPainter &painter)
{
    switch (lives) {
    case 3: {
        for (int i = 0; i < 3; ++i) {
            painter.drawPixmap(chairCoords[i], pixChair);
        }
        break;
    }
    case 2: {
        for (int i = 0; i < 2; ++i) {
            painter.drawPixmap(chairCoords[i], pixChair);
        }
        break;
    }
    case 1: {
        painter.drawPixmap(chairCoords[0], pixChair);
        break;
    }
    default:
        break;
    }
}

void Widget::drawAll(QPainter &painter)
{
    // Draw all cans
    for (int i = 0; i < 4; ++i) {
        for (int j = 0; j < 4; ++j) {
            painter.drawPixmap(cansCoords[i][j], (j % 2) ? pixCans[j] : pixCans[j + 4]);
        }
    }

    // Draw all chiefs
    for (int i = 0; i < 4; ++i) {
        painter.drawPixmap(chiefCoords[i], pixChiefs[i]);
    }

    // Draw all chairs
    for (int i = 0; i < 3; ++i) {
        painter.drawPixmap(chairCoords[i], pixChair);
    }

    // Draw all broken caps
    for (int i = 0; i < 2; ++i) {
        painter.drawPixmap(brokenCoords[i], pixBroken[i]);
    }

    // Draw 88 + 88
    drawDigitPairs(88, 0, painter);
    drawDigitPairs(88, 1, painter);
}

void Widget::drawKeyHints(QPainter &painter)
{
    QColor colorBlack(0, 0, 0);
    QColor colorRed(255, 0, 0);

    QFont fontBig = painter.font();
    fontBig.setPixelSize(30);
    fontBig.setBold(true);
    painter.setFont(fontBig);
    QPoint coords[6];
    for (int i = 0; i < 2; ++i) {
        int offset;
        if (i % 2 == 0) {
            painter.setPen(colorRed);
            offset = 0;
        } else {
            painter.setPen(colorBlack);
            offset = 1;
        }

        for (int j = 0; j < 6; ++j) {
            coords[j].setX(hintsCoords[j].x() + offset);
            coords[j].setY(hintsCoords[j].y() + offset);
        }

        for (int k = 0; k < 4; ++k) {
            painter.drawText(coords[k], keys[k]);
        }
        //painter.drawText(coords[5], strPressKey);
        fontBig.setPixelSize(14);
        painter.setFont(fontBig);
        painter.drawText(coords[4], strPause);
        fontBig.setPixelSize(30);
        painter.setFont(fontBig);
    }

    drawGameText(coords[5].x(), coords[5].y(), strPressKey, painter);
}

void Widget::drawGameText(const int aX, const int aY, const QString &aStr, QPainter &painter)
{
    QColor colorBlack(0, 0, 0);
    QColor colorRed(255, 0, 0);

    QFont fontBig = painter.font();
    fontBig.setPixelSize(20);
    fontBig.setBold(true);
    painter.setFont(fontBig);

    for (int i = 0; i < 2; ++i) {
        int offset;
        if (i % 2 == 0) {
            painter.setPen(colorRed);
            offset = 0;
        } else {
            painter.setPen(colorBlack);
            offset = 1;
        }

        painter.drawText(aX + offset, aY + offset, aStr);
    }
}

void Widget::drawDigitPairs(int number, int pair, QPainter &painter)
{
    if (number < 0 && number > 99) {
        number = 88; // Overload
    }

    int firstDigit = number / 10;
    int secondDigit = number % 10;

    QPoint coordsFirst;
    QPoint coordsSecond;

    switch (pair) {
    case 0: { // First pair
        coordsFirst = digitCoords[0];
        coordsSecond = digitCoords[1];
        break;
    }
    case 1: { // Second pair
        coordsFirst = digitCoords[2];
        coordsSecond = digitCoords[3];
        break;
    }
    default:
        return;
        break;
    }

    painter.drawPixmap(coordsFirst, pixDigits[firstDigit]);
    painter.drawPixmap(coordsSecond, pixDigits[secondDigit]);
}

void Widget::pauseGame(bool aPause)
{
    if (aPause) {
        currentGameState = Pause;
    } else {
        currentGameState = TheGame;
    }
}

void Widget::stopAllSfx()
{
    s_got->stop();
    s_move->stop();
    s_start->stop();
    s_miss->stop();
    s_gameOver->stop();
}

QPixmap Widget::getCanPixmap() const
{
    return (sideState % 2) ? pixCans[canState] : pixCans[canState + 4];
}

QPoint Widget::getCanCoords() const
{
    return (canState != (-1)) ? cansCoords[sideState][canState] : QPoint(0, 0);
}


Widget::~Widget()
{
    /* Empty destructor */
}
