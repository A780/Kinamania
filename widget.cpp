#include "widget.h"

#include <QPainter>
#include <QFileInfo>
#include <QApplication>

#ifdef _DEBUG
#include <QDebug>
#endif

//const int coords[][] = ;

Widget::Widget(QWidget *parent)
    : QWidget(parent),
      screen_w(640), screen_h(399)
{
    sound = true;
    soundDelay = 75;

    keysDelay = 200;
    keysAvailable = false;

    // Check gfx and sfx dirs
    gfxDirAndFilesAvailable = checkAllGfxRes();
    sfxDirAndFilesAvailable = checkAllSfxRes();
    if (!gfxDirAndFilesAvailable) {
        dirName = ":/gfx/";
        gfxFiles = updateGfxListFiles(dirName);
    }

#ifdef _DEBUG
    qDebug() << "Using" << dirName << "directory." << sfxDirAndFilesAvailable;
    QString test;
    foreach (test, sfxFiles) {
        qDebug() << test;
    }
#endif

    initAll();

    resetAllVariables();

    currentGameState = MainScreen;

    // ------------------ Load gfx and sfx ------------------- //
    loadAllGfx();
    if (sfxDirAndFilesAvailable) {
        loadAllSfx();
    }
    // ------------------------------------------------------- //

    pixSurface = new QPixmap(screen_w, screen_h);

    timerID = startTimer(10);

    setFocusPolicy(Qt::StrongFocus); // For Keys!

    //setFixedSize(screen_w, screen_h);
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
    initDendyCoords();
    initButtonsCoords();

    initMouseCoords();

    initHintsCoords();

    initLevels();

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

void Widget::initDendyCoords()
{
    dendyCoords[0] = dendyCoords[1] = QPoint(212, 84);
}

void Widget::initButtonsCoords()
{
    buttonCoords[0] = QPoint(43, 245);
    buttonCoords[1] = QPoint(43, 311);
    buttonCoords[2] = QPoint(538, 246);
    buttonCoords[3] = QPoint(537, 313);
    buttonCoords[4] = QPoint(556, 33);
    buttonCoords[5] = QPoint(552, 73);
    buttonCoords[6] = QPoint(553, 115);
}

void Widget::initMouseCoords()
{
    mouseCoords[0] = QRect(QPoint(43, 245), QPoint(43, 245) + QPoint(62, 63));
    mouseCoords[1] = QRect(QPoint(43, 311), QPoint(43, 311) + QPoint(62, 60));
    mouseCoords[2] = QRect(QPoint(538, 246), QPoint(538, 246) + QPoint(58, 60));
    mouseCoords[3] = QRect(QPoint(537, 313), QPoint(537, 313) + QPoint(57, 56));
    mouseCoords[4] = QRect(QPoint(556, 33), QPoint(556, 33) + QPoint(42, 29));
    mouseCoords[5] = QRect(QPoint(552, 73), QPoint(552, 73) + QPoint(50, 31));
    mouseCoords[6] = QRect(QPoint(553, 115), QPoint(553, 115) + QPoint(47, 29));
}

void Widget::updateMouserCoords()
{
    float x = 640.0f / screen_w;
    float y = 399.0f / screen_h;

    mouseCoords[0] = QRect(QPoint(43 / x, 245 / y), QPoint(43 / x, 245 / y) + QPoint(62 / x, 63 / y));
    mouseCoords[1] = QRect(QPoint(43 / x, 311 / y), QPoint(43 / x, 311 / y) + QPoint(62 / x, 60 / y));
    mouseCoords[2] = QRect(QPoint(538 / x, 246 / y), QPoint(538 / x, 246 / y) + QPoint(58 / x, 60 / y));
    mouseCoords[3] = QRect(QPoint(537 / x, 313 / y), QPoint(537 / x, 313 / y) + QPoint(57 / x, 56 / y));
    mouseCoords[4] = QRect(QPoint(556 / x, 33 / y), QPoint(556 / x, 33 / y) + QPoint(42 / x, 29 / y));
    mouseCoords[5] = QRect(QPoint(552 / x, 73 / y), QPoint(552 / x, 73 / y) + QPoint(50 / x, 31 / y));
    mouseCoords[6] = QRect(QPoint(553 / x, 115 / y), QPoint(553 / x, 115 / y) + QPoint(47 / x, 29 / y));
}

int Widget::getScaleLevel() const
{
    int scale = 1;

    if ((screen_w >= 320 && screen_h <= 640) ||
            (screen_h >= 240 && screen_h <= 399)) {
        scale = 1;
    }

    if ((screen_w > 640 && screen_h <= 1280) ||
        (screen_h > 399 && screen_h <= 798)) {
        scale = 2;
    }

    if ((screen_w > 1280 && screen_h <= 2560) ||
        (screen_h > 798 && screen_h <= 1197)) {
        scale = 3;
    }

    return scale;
}

void Widget::initLevels()
{
    levels[0] = 100;
    levels[1] = 50;
    levels[2] = 30;
    levels[3] = 20;
    levels[4] = 18;
    levels[5] = 15;
    levels[6] = 10;
}

void Widget::initHintsCoords()
{
    hintsCoords[0] = QPoint(62, 288);
    hintsCoords[1] = QPoint(62, 351);
    hintsCoords[2] = QPoint(554, 288);
    hintsCoords[3] = QPoint(554, 351);
    hintsCoords[4] = QPoint(556, 135);
    hintsCoords[5] = QPoint(569, 52);
    hintsCoords[6] = QPoint(569, 94);
}

void Widget::initStrings()
{
    keys[0] = 'Q';
    keys[1] = 'A';
    keys[2] = 'P';
    keys[3] = 'L';

    strPause = tr("Pause");
    strPressKey = tr("Press any key to start the game!");
    strGameOver = tr("Game over!");

    strWindowTitle = tr("Kinamania - The Game");
}

void Widget::refreshDelay()
{
#ifdef _DEBUG
    qDebug() << "--------------- Scale Level is:" << getScaleLevel();
#endif

    if (score >= 0 && score < 10) {
        delay = levels[0] / getScaleLevel();
    }

    if (score >= 10 && score < 15) {
        delay = levels[1] / getScaleLevel();
    }

    if (score >= 15 && score < 25) {
        delay = levels[2] / getScaleLevel();
    }

    if (score >= 25 && score < 50) {
        delay = levels[3] / getScaleLevel();
    }

    if (score >= 50 && score < 75) {
        delay = levels[4] / getScaleLevel();
    }

    if (score >= 75 && score < 95) {
        delay = levels[5] / getScaleLevel();
    }

    if (score >= 95 && score < 100) {
        delay = levels[6] / getScaleLevel();
    }
}

void Widget::resetAllVariables()
{
    buttonState = (-1);
    msec = sideState = 0;
    canState = (-1);
    chiefState = 0;
    dendyState = (-1);
    dendyDelay = 0;
    score = 0;
    //    score = 0;
    lives = 0;
    //    lives = 3;
    delay = 100;
    gotIt = 0;
}

void Widget::paintEvent(QPaintEvent */*event*/)
{
    QPainter painter(this);

    if (screen_w != 640 && screen_h != 399) {
        painter.drawPixmap(0, 0, pixSurface->scaled(screen_w, screen_h, Qt::IgnoreAspectRatio, Qt::SmoothTransformation));
    } else {
        painter.drawPixmap(0, 0, *pixSurface);
    }

#ifdef _DEBUG
    drawRectangles(painter);
#endif
}

void Widget::timerEvent(QTimerEvent */*event*/)
{
    if (!sfxDirAndFilesAvailable) {
        emit disableSound();
        sound = false;
    }

    int num = qrand() % 16;
    int dendy = qrand() % 100;

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
        if (sound) {
            stopAllSfx();
        }
        if (sound && s_gameOver->isFinished()) {
#ifdef _DEBUG
            qDebug() << "############### Is playing?";
#endif
            s_gameOver->play();
        }
    }

    if (msec == soundDelay && currentGameState == TheWon) {
        if (sound) {
            stopAllSfx();
        }
        if (sound && s_gameOver->isFinished()) {
            s_Win->play();
        }
    }

    if (msec >= delay && currentGameState == TheGame) { // 100 is one sec
        msec = 0;

        if (dendyState == (-1)) {
            if (dendy >= 20 && dendy < 25) {
            //if (1) {
                if (!(dendyDelay > 0)) {
                    dendyDelay = 4;
                }
            }
        }

        if (dendyDelay >= 0) {
            --dendyDelay;
        }

        if (dendyDelay <= 0 && dendyState != (-1)) {
            dendyState = (-1);
        }

#ifdef _DEBUG
        qDebug() << "############### Dendy" << dendyDelay << dendyState << dendy;
#endif

        switch (dendyDelay) {
        case 3:
        case 2: {
            dendyState = 0;
            break;
        }
        case 1:
        case 0: {
            dendyState = 1;
            break;
        }
        default:
            break;
        }

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
        } else if (canState == 4 && sideState != chiefState && dendyState == (-1)) {
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
        chiefState = buttonState = 0;
        break;
    }
    case Qt::Key_P:
    case Qt::Key_9: {
        chiefState = 1;
        buttonState = 2;
        break;
    }
    case Qt::Key_A:
    case Qt::Key_1: {
        chiefState = 2;
        buttonState = 1;
        break;
    }
    case Qt::Key_L:
    case Qt::Key_3: {
        chiefState = 3;
        buttonState = 3;
        break;
    }
    case Qt::Key_Pause:
    case Qt::Key_G: {
        buttonState = 6;
        if (!state) {
            pauseGame(currentGameState != Pause);
        }
        break;
    }
    case Qt::Key_F6: {
        buttonState = 5;
        break;
    }
    case Qt::Key_F5: {
        buttonState = 4;
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
    case Qt::Key_3:
    case Qt::Key_Pause:
    case Qt::Key_G:
    case Qt::Key_F6:
    case Qt::Key_F5: {
        //chiefState = (-1);
        buttonState = (-1);
        break;
    }
    default:
        break;
    }
}

void Widget::mousePressEvent(QMouseEvent *event)
{
#ifdef _DEBUG
    qDebug() << "MousePress" << event->pos();
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

    if (mouseCoords[0].contains(event->pos())) {
        chiefState = buttonState = 0;
    }

    if (mouseCoords[2].contains(event->pos())) {
        chiefState = 1;
        buttonState = 2;
    }

    if (mouseCoords[1].contains(event->pos())) {
        chiefState = 2;
        buttonState = 1;
    }

    if (mouseCoords[3].contains(event->pos())) {
        chiefState = 3;
        buttonState = 3;
    }

    if (mouseCoords[4].contains(event->pos())) {
        buttonState = 4;
        slotStartNewGame();
    }

    if (mouseCoords[5].contains(event->pos())) {
        buttonState = 5;
    }

    if (mouseCoords[6].contains(event->pos())) {
        buttonState = 6;
        if (!state) {
            pauseGame(currentGameState != Pause);
        }
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
#ifdef _DEBUG
    qDebug() << "MouseRelease" << event->pos();
#endif
    for (int i = 0; i < 7; ++i) {
        if (mouseCoords[i].contains(event->pos())) {
            buttonState = (-1);
        }
    }
}

void Widget::slotEnableSound(bool aSound)
{
#ifdef _DEBUG
    qDebug() << "Sound" << aSound;
#endif
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

void Widget::slotSetPixmapSize(int w, int h)
{
    screen_w = w;
    screen_h = h;

    updateMouserCoords();
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
        drawButtons(painter);
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

        // Draw Dendy
        if (dendyState != (-1)) {
            painter.drawPixmap(dendyCoords[dendyState], pixDendy[dendyState]);
        }

        // Draw chairbar
        drawChairBar(painter);

        // Draw 90 + score
        drawDigitPairs(90, 0, painter);
        drawDigitPairs(score, 1, painter);

        // Draw buttons
        drawButtons(painter);
        break;
    }
    case TheWon: {
        painter.drawPixmap(0, 0, pixWonScreen);
        break;
    }
    case GameOver: {
        drawAll(painter);
        drawGameText(strGameOver, painter);
        drawButtons(painter);
        break;
    }
    case Pause: {
        drawGameText(strPause, painter);
        drawButtons(painter);
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

    // Draw Dendy
    for (int i = 0; i < 2; ++i) {
        painter.drawPixmap(dendyCoords[i], pixDendy[i]);
    }

    // Draw all buttons
    //    for (int i = 0; i < 7; ++i) {
    //        painter.drawPixmap(buttonCoords[i], pixButtons[i]);
    //    }
}

void Widget::drawKeyHints(QPainter &painter)
{
    QColor colorBlack(0, 0, 0);
    QColor colorOrange(255, 140, 0);

    QFont fontBig = painter.font();
    fontBig.setPixelSize(30);
    fontBig.setBold(true);

    QFont fontSmall = painter.font();
    fontSmall.setPixelSize(14);
    fontSmall.setBold(true);

    painter.setFont(fontBig);

    QPoint coords[6];
    for (int i = 0; i < 2; ++i) {
        int offset;
        if (i % 2 == 0) {
            painter.setPen(colorOrange);
            offset = 0;
        } else {
            painter.setPen(colorBlack);
            offset = 1;
        }

        for (int j = 0; j < 7; ++j) {
            coords[j].setX(hintsCoords[j].x() + offset);
            coords[j].setY(hintsCoords[j].y() + offset);
        }

        for (int k = 0; k < 4; ++k) {
            painter.drawText(coords[k], keys[k]);
        }

        painter.setFont(fontSmall);

        painter.drawText(coords[4], strPause);
        painter.drawText(coords[5], tr("F5"));
        painter.drawText(coords[6], tr("F6"));

        painter.setFont(fontBig);
    }

    drawGameText(strPressKey, painter);
}

void Widget::drawGameText(const QString &aStr, QPainter &painter)
{
    QColor colorBlack(0, 0, 0);
    QColor colorRed(255, 255, 255);

    int f_offset = 30;

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

        painter.drawText(0, 0, 640, painter.font().pixelSize() + f_offset + offset,
                         Qt::AlignHCenter | Qt::AlignVCenter, aStr);
    }
}

void Widget::drawButtons(QPainter &painter)
{
    if (buttonState != (-1)) {
        painter.drawPixmap(buttonCoords[buttonState], pixButtons[buttonState]);
    }
}

#ifdef _DEBUG
void Widget::drawRectangles(QPainter &painter)
{
    painter.setPen(QPen(Qt::black, 2));
    for (int i = 0; i < 7; ++i) {
        painter.drawRect(mouseCoords[i]);
    }
}
#endif

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

bool Widget::checkAllGfxRes()
{
    gfxFiles = getAllGfxFiles();

    dirName = qApp->applicationDirPath() + "/gfx/";
    QFileInfo dirInfo(dirName);

    if (!dirInfo.isDir() && !dirInfo.isReadable()) {
        return false;
    } else {
        gfxFiles = updateGfxListFiles(dirName);
        QString fileName;
        foreach (fileName, gfxFiles) {
            QFileInfo fileInfo(fileName);
            if (!fileInfo.isFile() && !fileInfo.isReadable()) {
                return false;
            }
        }
    }
    return true;
}

bool Widget::checkAllSfxRes()
{
    sfxFiles = getAllSfxFiles();

    dirName = qApp->applicationDirPath() + "/sfx/";
    QFileInfo dirInfo(dirName);
    QStringList filesList;
    if (!dirInfo.isDir() && !dirInfo.isReadable()) {
        return false;
    } else {
        QString fileName;
        foreach (fileName, sfxFiles) {
            filesList << dirName + fileName;
        }

        foreach (fileName, filesList) {
            QFileInfo fileInfo(fileName);
            if (!fileInfo.isFile() && !fileInfo.isReadable()) {
                return false;
            }
        }
    }
    sfxFiles = filesList;
    return true;
}

QStringList Widget::getAllSfxFiles() const
{
    QStringList sfxFiles;
    sfxFiles << "Got.wav" << "Move.wav"
             << "Start.wav" << "Miss.wav"
             << "Gameover.wav" << "Win.wav";
    return sfxFiles;
}

void Widget::loadAllSfx()
{
    s_got = new QSound(sfxFiles[0], this);
    s_move = new QSound(sfxFiles[1], this);
    s_start = new QSound(sfxFiles[2], this);
    s_miss = new QSound(sfxFiles[3], this);
    s_gameOver = new QSound(sfxFiles[4], this);
    s_Win = new QSound(sfxFiles[5], this);
}

QStringList Widget::getAllGfxFiles() const
{
    QStringList listOfGfxFiles;

    listOfGfxFiles << "background.png";

    for (int i = 0; i < 8; ++i) {
        listOfGfxFiles << QString("can_%1.png").arg(i);
    }

    for (int i = 0; i < 4; ++i) {
        listOfGfxFiles << QString("chief_%1.png").arg(i);
    }

    for (int i = 0; i < 2; ++i) {
        listOfGfxFiles << QString("broken_%1.png").arg(i);
    }

    for (int i = 0; i < 2; ++i) {
        listOfGfxFiles << QString("dendy_%1.png").arg(i);
    }

    for (int i = 0; i < 10; ++i) {
        listOfGfxFiles << QString("digit_%1.png").arg(i);
    }

    for (int i = 0; i < 7; ++i) {
        listOfGfxFiles << QString("button_%1.png").arg(i);
    }

    listOfGfxFiles << "chair.png";
    listOfGfxFiles << "bsod.png";

    return listOfGfxFiles;
}

QStringList Widget::updateGfxListFiles(const QString &dirName)
{
    QString fileName;
    QStringList filesList;
    gfxFiles = getAllGfxFiles();
    foreach (fileName, gfxFiles) {
        filesList << dirName + fileName;
    }
    return filesList;
}

void Widget::loadAllGfx()
{
    pixBackground.load(gfxFiles[0]); // Load background

    for (int i = 1; i < 9; ++i) { // 8 is count of frames of cans
        pixCans[i - 1].load(gfxFiles[i]);
    }

    for (int i = 9; i < 13; ++i) { // 4 state of chief
        pixChiefs[i - 9].load(gfxFiles[i]);
    }

    for (int i = 13; i < 15; ++i) { // 2 state of broken pepsi can
        pixBroken[i - 13].load(gfxFiles[i]);
    }

    for (int i = 15; i < 17; ++i) { // 2 state of dendy
        pixDendy[i - 15].load(gfxFiles[i]);
    }

    for (int i = 17; i < 27; ++i) { // 10 LCD digits
        pixDigits[i - 17].load(gfxFiles[i]);
    }

    for (int i = 27; i < 34; ++i) { // 7 pushed buttons
        pixButtons[i - 27].load(gfxFiles[i]);
    }

    pixChair.load(gfxFiles[34]); // Load chair

    pixWonScreen.load(gfxFiles[35]); // Load won screen*/
}

Widget::~Widget()
{
    /* Empty destructor */
}
