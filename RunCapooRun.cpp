#include "RunCapooRun.h"
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <QTimer>
#include <Qpoint>
#include <QtMultimedia/QSound>

RunCapooRun::RunCapooRun(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    startClick = 0;      // click of the start botton
    window = 0;          // main window : 0, game window : 1, countdown window : 2, gameover window : 3
    pos = 2;             // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
    capoo = 1;           // capoo's status
    frequency = 100;     // initial frequency
    countdown = 1;       // for countdown window usage
    movingTimer = 0;     // counting time (1 time per second
    setObsTable();       // set obstacle coordinate table
    ending_counter = 0;  // initialize counter
    score = -3;
    score_capoo = 1;
    // -----below is for QSound initialization-----
    for (int i = 0; i < 10; i++) sound[i] = false;
    wav0 = new QSound(".\\src\\sounds\\Trap Adventures 2 - Water Levels Music.wav", this);
    wav0->setLoops(-1);  // 循環次數 -1代表無限循環
    wav1 = new QSound(".\\src\\sounds\\contedefees_0124.wav", this);
    wav1->setLoops(-1);
    wav2 = new QSound(".\\src\\sounds\\button sound effect.wav", this);
}

void RunCapooRun::paintEvent(QPaintEvent*) {
    // print window
    QPixmap pixmap;
    QPainter painter(this);

    // starting window
    if (window == 0) {
        // show welcome pic
        pixmap.load(".\\src\\main.png");
        painter.drawPixmap(0, 0, pixmap);

        // bgm
        if (!sound[1]) {
            wav1->play();
            sound[1] = true;
        }

        // show start button
        pixmap.load(".\\src\\button\\start.png");
        painter.drawPixmap(450, 480, pixmap);
        if (startClick) {
            pixmap.load(".\\src\\button\\started.png");
            painter.drawPixmap(450, 480, pixmap);
            window = 2;
            repaint();
        }
    }

    // gaming window
    else if (window == 1) {
        //delete the timer and create a new one
        killTimer(timer);
        timer = startTimer(frequency);

        // background pic
        pixmap.load(".\\src\\background\\XP_with_board.png");
        painter.drawPixmap(0, 0, pixmap);

        // background music
        wav1->stop();
        sound[1] = false;
        if (!sound[0]) {
            wav0->play();
            sound[0] = true;
        }

        if (score >= 0) {
            // score board
            if (score % 10 == 0)
                pixmap.load(".\\src\\score\\0.png");
            else if (score % 10 == 1)
                pixmap.load(".\\src\\score\\1.png");
            else if (score % 10 == 2)
                pixmap.load(".\\src\\score\\2.png");
            else if (score % 10 == 3)
                pixmap.load(".\\src\\score\\3.png");
            else if (score % 10 == 4)
                pixmap.load(".\\src\\score\\4.png");
            else if (score % 10 == 5)
                pixmap.load(".\\src\\score\\5.png");
            else if (score % 10 == 6)
                pixmap.load(".\\src\\score\\6.png");
            else if (score % 10 == 7)
                pixmap.load(".\\src\\score\\7.png");
            else if (score % 10 == 8)
                pixmap.load(".\\src\\score\\8.png");
            else if (score % 10 == 9)
                pixmap.load(".\\src\\score\\9.png");
            painter.drawPixmap(1060, 60, pixmap);

            if (score / 10 == 0)
                pixmap.load(".\\src\\score\\0.png");
            else if (score / 10 == 1)
                pixmap.load(".\\src\\score\\1.png");
            else if (score / 10 == 2)
                pixmap.load(".\\src\\score\\2.png");
            else if (score / 10 == 3)
                pixmap.load(".\\src\\score\\3.png");
            else if (score / 10 == 4)
                pixmap.load(".\\src\\score\\4.png");
            else if (score / 10 == 5)
                pixmap.load(".\\src\\score\\5.png");
            else if (score / 10 == 6)
                pixmap.load(".\\src\\score\\6.png");
            else if (score / 10 == 7)
                pixmap.load(".\\src\\score\\7.png");
            else if (score / 10 == 8)
                pixmap.load(".\\src\\score\\8.png");
            else if (score / 10 == 9)
                pixmap.load(".\\src\\score\\9.png");
            painter.drawPixmap(1010, 60, pixmap);
        }

        //score capoo gif
        if (score_capoo == 1)
            pixmap.load(".\\src\\score_capoo\\11.png");
        else if (score_capoo == 2)
            pixmap.load(".\\src\\score_capoo\\22.png");
        else if (score_capoo == 3)
            pixmap.load(".\\src\\score_capoo\\3.png");
        else if (score_capoo == 4)
            pixmap.load(".\\src\\score_capoo\\4.png");
        else if (score_capoo == 5)
            pixmap.load(".\\src\\score_capoo\\5.png");
        else if (score_capoo == 6)
            pixmap.load(".\\src\\score_capoo\\6.png");
        else if (score_capoo == 7)
            pixmap.load(".\\src\\score_capoo\\5.png");
        else if (score_capoo == 8)
            pixmap.load(".\\src\\score_capoo\\4.png");
        else if (score_capoo == 9)
            pixmap.load(".\\src\\score_capoo\\3.png");
        else if (score_capoo == 10)
            pixmap.load(".\\src\\score_capoo\\22.png");
        else if (score_capoo == 11) {
            pixmap.load(".\\src\\score_capoo\\11.png");
            score_capoo = 0;
        }
        painter.drawPixmap(885, 20, pixmap);
        score_capoo++;

        // layout grass
        {
            pixmap.load(".\\src\\grass\\9.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row9.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][9][0], obstacle_table[i][9][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\8.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row8.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][8][0], obstacle_table[i][8][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\7.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row7.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][7][0], obstacle_table[i][7][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\6.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row6.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][6][0], obstacle_table[i][6][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\5.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row5.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][5][0], obstacle_table[i][5][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\4.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row4.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][4][0], obstacle_table[i][4][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\3.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row3.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][3][0], obstacle_table[i][3][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\2.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row2.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][2][0], obstacle_table[i][2][1], pixmap);
                }
            }
            pixmap.load(".\\src\\grass\\1.png");
            for (int i = 0; i < 5; i++) {
                if (*(&row1.send() + i) == 0) {
                    painter.drawPixmap(obstacle_table[i][1][0], obstacle_table[i][1][1], pixmap);
                }
            }
        }
        // capoo gif
        {
            if (capoo == 1)
                pixmap.load(".\\src\\capoo_gif\\1.png");
            else if (capoo == 2)
                pixmap.load(".\\src\\capoo_gif\\2.png");
            else if (capoo == 3)
                pixmap.load(".\\src\\capoo_gif\\3.png");
            else if (capoo == 4)
                pixmap.load(".\\src\\capoo_gif\\4.png");
            else if (capoo == 5)
                pixmap.load(".\\src\\capoo_gif\\5.png");
            else if (capoo == 6)
                pixmap.load(".\\src\\capoo_gif\\6.png");
        }
        capoo++;
        if (capoo > 6) capoo = 1;
        painter.drawPixmap(250 * pos - 50, 425, pixmap);  // 400 320 -> 450 370

        // 讓咖波顯示在第0排障礙物後面
        pixmap.load(".\\src\\grass\\0.png");
        for (int i = 0; i < 5; i++) {
            if (*(&row0.send() + i) == 0) {
                painter.drawPixmap(obstacle_table[i][0][0], obstacle_table[i][0][1], pixmap);
            }
        }
    }

    // loading window
    else if (window == 2) {
        killTimer(timer);         // kill the previous timer
        timer = startTimer(100);  // set a new timer
        if (countdown > 50) {
            window = 1;  // end countdown
            // initialize everything in gaming window
            frequency = 100;
            create_counter = 0;
            movingTimer = 0;
            score = -3;
        }

        // background pic
        pixmap.load(".\\src\\loading\\bg.png");
        painter.drawPixmap(0, 0, pixmap);

        // countdown gif
        {
            if (countdown == 0)
                pixmap.load(".\\src\\loading\\000.jpg");
            else if (countdown == 1)
                pixmap.load(".\\src\\loading\\001.jpg");
            else if (countdown == 2)
                pixmap.load(".\\src\\loading\\002.jpg");
            else if (countdown == 3)
                pixmap.load(".\\src\\loading\\003.jpg");
            else if (countdown == 4)
                pixmap.load(".\\src\\loading\\004.jpg");
            else if (countdown == 5)
                pixmap.load(".\\src\\loading\\005.jpg");
            else if (countdown == 6)
                pixmap.load(".\\src\\loading\\006.jpg");
            else if (countdown == 7)
                pixmap.load(".\\src\\loading\\007.jpg");
            else if (countdown == 8)
                pixmap.load(".\\src\\loading\\008.jpg");
            else if (countdown == 9)
                pixmap.load(".\\src\\loading\\009.jpg");
            else if (countdown == 10)
                pixmap.load(".\\src\\loading\\010.jpg");
            else if (countdown == 11)
                pixmap.load(".\\src\\loading\\011.jpg");
            else if (countdown == 12)
                pixmap.load(".\\src\\loading\\012.jpg");
            else if (countdown == 13)
                pixmap.load(".\\src\\loading\\013.jpg");
            else if (countdown == 14)
                pixmap.load(".\\src\\loading\\014.jpg");
            else if (countdown == 15)
                pixmap.load(".\\src\\loading\\015.jpg");
            else if (countdown == 16)
                pixmap.load(".\\src\\loading\\016.jpg");
            else if (countdown == 17)
                pixmap.load(".\\src\\loading\\017.jpg");
            else if (countdown == 18)
                pixmap.load(".\\src\\loading\\018.jpg");
            else if (countdown == 19)
                pixmap.load(".\\src\\loading\\019.jpg");
            else if (countdown == 20)
                pixmap.load(".\\src\\loading\\020.jpg");
            else if (countdown == 21)
                pixmap.load(".\\src\\loading\\021.jpg");
            else if (countdown == 22)
                pixmap.load(".\\src\\loading\\022.jpg");
            else if (countdown == 23)
                pixmap.load(".\\src\\loading\\023.jpg");
            else if (countdown == 24)
                pixmap.load(".\\src\\loading\\024.jpg");
            else if (countdown == 25)
                pixmap.load(".\\src\\loading\\025.jpg");
            else if (countdown == 26)
                pixmap.load(".\\src\\loading\\026.jpg");
            else if (countdown == 27)
                pixmap.load(".\\src\\loading\\027.jpg");
            else if (countdown == 28)
                pixmap.load(".\\src\\loading\\028.jpg");
            else if (countdown == 29)
                pixmap.load(".\\src\\loading\\029.jpg");
            else if (countdown == 30)
                pixmap.load(".\\src\\loading\\030.jpg");
            else if (countdown == 31)
                pixmap.load(".\\src\\loading\\031.jpg");
            else if (countdown == 32)
                pixmap.load(".\\src\\loading\\032.jpg");
            else if (countdown == 33)
                pixmap.load(".\\src\\loading\\033.jpg");
            else if (countdown == 34)
                pixmap.load(".\\src\\loading\\034.jpg");
            else if (countdown == 35)
                pixmap.load(".\\src\\loading\\035.jpg");
            else if (countdown == 36)
                pixmap.load(".\\src\\loading\\036.jpg");
            else if (countdown == 37)
                pixmap.load(".\\src\\loading\\037.jpg");
            else if (countdown == 38)
                pixmap.load(".\\src\\loading\\038.jpg");
            else if (countdown == 39)
                pixmap.load(".\\src\\loading\\039.jpg");
            else if (countdown == 40)
                pixmap.load(".\\src\\loading\\040.jpg");
            else if (countdown == 41)
                pixmap.load(".\\src\\loading\\041.jpg");
            else if (countdown == 42)
                pixmap.load(".\\src\\loading\\042.jpg");
            else if (countdown == 43)
                pixmap.load(".\\src\\loading\\043.jpg");
            else if (countdown == 44)
                pixmap.load(".\\src\\loading\\044.jpg");
            else if (countdown == 45)
                pixmap.load(".\\src\\loading\\045.jpg");
            else if (countdown == 46)
                pixmap.load(".\\src\\loading\\046.jpg");
            else if (countdown == 47)
                pixmap.load(".\\src\\loading\\047.jpg");
            else if (countdown == 48)
                pixmap.load(".\\src\\loading\\048.jpg");
            else if (countdown == 49)
                pixmap.load(".\\src\\loading\\049.jpg");
            else if (countdown == 50)
                pixmap.load(".\\src\\loading\\050.jpg");
        }
        countdown++;

        painter.drawPixmap(360, 176, pixmap);
    }

    // gameover window
    else if (window == 3) {
        // stop playing_bgm
        if (sound) {
            wav0->stop();
            sound[0] = false;
        }

        killTimer(timer);
        timer = startTimer(150);
        pixmap.load(".\\src\\gameover\\bg.png");
        painter.drawPixmap(0, 0, pixmap);
        pixmap.load(".\\src\\gameover\\flat_capoo.png");
        painter.drawPixmap(30, 0, pixmap);

        QPixmap p1, p2, p3;  // extra pixmaps

        // *gameover*
        {
            if (ending_counter % 29 == 0 || ending_counter % 29 == 1)
                p1.load(".\\src\\gameover\\gameover\\0.png");
            else if (ending_counter % 29 == 2 || ending_counter % 29 == 3)
                p1.load(".\\src\\gameover\\gameover\\1.png");
            else if (ending_counter % 29 == 4 || ending_counter % 29 == 5)
                p1.load(".\\src\\gameover\\gameover\\2.png");
            else if (ending_counter % 29 == 6 || ending_counter % 29 == 7)
                p1.load(".\\src\\gameover\\gameover\\3.png");
            else if (ending_counter % 29 == 8 || ending_counter % 29 == 9)
                p1.load(".\\src\\gameover\\gameover\\4.png");
            else if (ending_counter % 29 == 10 || ending_counter % 29 == 11)
                p1.load(".\\src\\gameover\\gameover\\5.png");
            else if (ending_counter % 29 == 12 || ending_counter % 29 == 13)
                p1.load(".\\src\\gameover\\gameover\\6.png");
            else if (ending_counter % 29 == 14 || ending_counter % 29 == 15)
                p1.load(".\\src\\gameover\\gameover\\7.png");
            else if (ending_counter % 29 == 16 || ending_counter % 29 == 17)
                p1.load(".\\src\\gameover\\gameover\\8.png");
            else if (ending_counter % 29 == 18 || ending_counter % 29 == 19)
                p1.load(".\\src\\gameover\\gameover\\9.png");
            else if (ending_counter % 29 == 20 || ending_counter % 29 == 21)
                p1.load(".\\src\\gameover\\gameover\\10.png");
            else if (ending_counter % 29 == 22 || ending_counter % 29 == 23)
                p1.load(".\\src\\gameover\\gameover\\11.png");
            else if (ending_counter % 29 == 24 || ending_counter % 29 == 25)
                p1.load(".\\src\\gameover\\gameover\\12.png");
            else if (ending_counter % 29 == 26 || ending_counter % 29 == 27)
                p1.load(".\\src\\gameover\\gameover\\13.png");
            else if (ending_counter >= 28) {
                window = 0;
                startClick = 0;      // click of the start botton
                pos = 2;             // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
                capoo = 1;           // capoo's status
                frequency = 100;     // initial frequency
                countdown = 0;       // for countdown window usage
                movingTimer = 0;     // counting time (1 time per second
                ending_counter = 0;  // initialize counter
                score = -3;          // initialize score
            }
        }
        // *yes*
        {
            if (ending_counter % 5 == 0)
                p2.load(".\\src\\gameover\\yes\\0.png");
            else if (ending_counter % 5 == 1)
                p2.load(".\\src\\gameover\\yes\\1.png");
            else if (ending_counter % 5 == 2)
                p2.load(".\\src\\gameover\\yes\\2.png");
            else if (ending_counter % 5 == 3)
                p2.load(".\\src\\gameover\\yes\\3.png");
            else if (ending_counter % 5 == 4)
                p2.load(".\\src\\gameover\\yes\\4.png");
        }
        // *no*
        {
            if (ending_counter % 12 == 0)
                p3.load(".\\src\\gameover\\no\\0.png");
            else if (ending_counter % 12 == 1)
                p3.load(".\\src\\gameover\\no\\1.png");
            else if (ending_counter % 12 == 2)
                p3.load(".\\src\\gameover\\no\\2.png");
            else if (ending_counter % 12 == 3)
                p3.load(".\\src\\gameover\\no\\3.png");
            else if (ending_counter % 12 == 4)
                p3.load(".\\src\\gameover\\no\\4.png");
            else if (ending_counter % 12 == 5)
                p3.load(".\\src\\gameover\\no\\5.png");
            else if (ending_counter % 12 == 6)
                p3.load(".\\src\\gameover\\no\\6.png");
            else if (ending_counter % 12 == 7)
                p3.load(".\\src\\gameover\\no\\7.png");
            else if (ending_counter % 12 == 8)
                p3.load(".\\src\\gameover\\no\\8.png");
            else if (ending_counter % 12 == 9)
                p3.load(".\\src\\gameover\\no\\9.png");
            else if (ending_counter % 12 == 10)
                p3.load(".\\src\\gameover\\no\\10.png");
            else if (ending_counter % 12 == 11)
                p3.load(".\\src\\gameover\\no\\11.png");
        }
        painter.drawPixmap(300, 50, p1);
        painter.drawPixmap(100, 350, p2);
        painter.drawPixmap(885, 375, p3);

        ending_counter++;
    }
}

void RunCapooRun::mouseReleaseEvent(QMouseEvent* evt) {
    repaint();

    //　start button pressed
    if (!window) {
        wav2->play();
        QPoint point = evt->pos();
        if ((point.x() > 450 && point.x() < 750) && (point.y() > 470 && point.y() < 550)) {
            startClick = (!startClick);
        }
    }

    // gaming operations
    else if (window == 1) {
        if (evt->button() == Qt::LeftButton && pos > 0)
            pos--;
        else if (evt->button() == Qt::RightButton && pos < 4)
            pos++;
    }

    // gameover window
    else if (window == 3) {
        startClick = 0;      // click of the start botton
        pos = 2;             // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
        capoo = 1;           // capoo's status
        frequency = 100;     // initial frequency
        countdown = 0;       // for countdown window usage
        movingTimer = 0;     // counting time (1 time per second
        ending_counter = 0;  // initialize counter
        score = -3;          // initialize score

        QPoint point = evt->pos();

        if ((point.x() > 100 && point.x() < 320) && (point.y() > 350 && point.y() < 570))
            window = 2;  // yes
        else if ((point.x() > 885 && point.x() < 1080) && (point.y() > 375 && point.y() < 595))
            window = 0;  //no
    }
    repaint();
}

void RunCapooRun::timerEvent(QTimerEvent* evt) {
    repaint();  //refresh

    movingTimer++;  // count to 1 sec, per "movingTimer" is a "100 micro sec"

    // when it accumulates to 1 sec, reset the counter and push the map
    if (movingTimer == 10 && window == 1) {
        movingTimer = 0;  //reset
        create_counter++;
        if (frequency > 30) frequency -= 0.5;  // let game getting faster

        //傳遞 ( row1 ~ row8 )
        row0.receive(row1.send());
        row1.receive(row2.send());
        row2.receive(row3.send());
        row3.receive(row4.send());
        row4.receive(row5.send());
        row5.receive(row6.send());
        row6.receive(row7.send());
        row7.receive(row8.send());
        row8.receive(row9.send());
        //生成 ( row9 )
        if (create_counter == 3) create_counter = 0;  //歸零
        if (create_counter == 0) {
            row9.reset();   // 刷新成空行
            row9.create();  // 生成障礙物行
            score++;        //　計分
        } else
            row9.reset();  // 輸出空行
    }

    // losing game
    if (*(&row0.send() + pos) == 0) {
        row0.reset();
        row1.reset();
        row2.reset();
        row3.reset();
        row4.reset();
        row5.reset();
        row6.reset();
        row7.reset();
        row8.reset();
        row9.reset();
        window = 3;
    }
}

void RunCapooRun::setObsTable() {
    // key ( x, y in pixel) into (x, y in coordinate plane)
    //0
    obstacle_table[0][0][0] = -100;  // 0
    obstacle_table[0][0][1] = 480;
    obstacle_table[1][0][0] = 155;  // 1
    obstacle_table[1][0][1] = 490;
    obstacle_table[2][0][0] = 510;  // 2
    obstacle_table[2][0][1] = 490;
    obstacle_table[3][0][0] = 825;  // 3
    obstacle_table[3][0][1] = 490;
    obstacle_table[4][0][0] = 1130;  // 4
    obstacle_table[4][0][1] = 485;
    //1
    for (int i = 0; i < 5; i++) obstacle_table[i][1][1] = 465;
    obstacle_table[0][1][0] = -30;
    obstacle_table[1][1][0] = 205;
    obstacle_table[2][1][0] = 505;
    obstacle_table[3][1][0] = 790;
    obstacle_table[4][1][0] = 1040;
    //2
    for (int i = 0; i < 5; i++) obstacle_table[i][2][1] = 445;
    obstacle_table[0][2][0] = 40;
    obstacle_table[1][2][0] = 235;
    obstacle_table[2][2][0] = 508;
    obstacle_table[3][2][0] = 757;
    obstacle_table[4][2][0] = 975;
    //3
    for (int i = 0; i < 5; i++) obstacle_table[i][3][1] = 435;
    obstacle_table[0][3][0] = 55;
    obstacle_table[1][3][0] = 250;
    obstacle_table[2][3][0] = 508;
    obstacle_table[3][3][0] = 735;
    obstacle_table[4][3][0] = 950;
    //4
    for (int i = 0; i < 5; i++) obstacle_table[i][4][1] = 425;
    obstacle_table[0][4][0] = 110;
    obstacle_table[1][4][0] = 285;
    obstacle_table[2][4][0] = 510;
    obstacle_table[3][4][0] = 707;
    obstacle_table[4][4][0] = 910;
    //5
    for (int i = 0; i < 5; i++) obstacle_table[i][5][1] = 415;
    obstacle_table[0][5][0] = 150;
    obstacle_table[1][5][0] = 315;
    obstacle_table[2][5][0] = 511;
    obstacle_table[3][5][0] = 690;
    obstacle_table[4][5][0] = 865;
    //6
    for (int i = 0; i < 5; i++) obstacle_table[i][6][1] = 405;
    obstacle_table[0][6][0] = 190;
    obstacle_table[1][6][0] = 347;
    obstacle_table[2][6][0] = 513;
    obstacle_table[3][6][0] = 665;
    obstacle_table[4][6][0] = 810;
    //7
    for (int i = 0; i < 5; i++) obstacle_table[i][7][1] = 395;
    obstacle_table[0][7][0] = 230;
    obstacle_table[1][7][0] = 377;
    obstacle_table[2][7][0] = 514;
    obstacle_table[3][7][0] = 638;
    obstacle_table[4][7][0] = 760;
    //8
    for (int i = 0; i < 5; i++) obstacle_table[i][8][1] = 385;
    obstacle_table[0][8][0] = 285;
    obstacle_table[1][8][0] = 407;
    obstacle_table[2][8][0] = 516;
    obstacle_table[3][8][0] = 608;
    obstacle_table[4][8][0] = 720;
    //9
    for (int i = 0; i < 5; i++) obstacle_table[i][9][1] = 375;
    obstacle_table[0][9][0] = 340;
    obstacle_table[1][9][0] = 438;
    obstacle_table[2][9][0] = 517;
    obstacle_table[3][9][0] = 582;
    obstacle_table[4][9][0] = 675;
}
