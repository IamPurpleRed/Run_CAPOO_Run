#include "RunCapooRun.h"
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QPixmap>
#include <QSize>
#include <QTimer>
#include <Qpoint>

RunCapooRun::RunCapooRun(QWidget* parent)
    : QMainWindow(parent) {
    ui.setupUi(this);

    startClick = 0;   // click of the start botton
    window = 0;       // main window : 0, game window : 1, countdown window : 2
    pos = 2;          // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
    capoo = 1;        // capoo's status
    frequency = 100;  // initial frequency
    countdown = 1;    // for countdown window usage
    movingTimer = 0;  // counting time (1 time per second
    setObsTable();    // set obstacle coordinate table
}

void RunCapooRun::paintEvent(QPaintEvent*) {
    // print window
    QPixmap pixmap;
    QPainter painter(this);

    if (flag == 1) {
        pixmap.load(".\\src\\original\\bug.jpg");
        painter.drawPixmap(0, 0, pixmap);
        timer = startTimer(10);
    }

    // starting window
    if (window == 0) {
        // show welcome pic
        pixmap.load(".\\src\\main.png");
        painter.drawPixmap(0, 0, pixmap);

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

    // countdown window
    else if (window == 2) {
        killTimer(timer);         // kill the previous timer
        timer = startTimer(100);  // set a new timer
        if (countdown > 30) {
            window = 1;  // end countdown
            // initialize everything in gaming window
            frequency = 100;
            create_counter = 0;
            movingTimer = 0;
        }

        // background pic
        pixmap.load(".\\src\\background\\XP_blur.png");
        painter.drawPixmap(0, 0, pixmap);

        // countdown gif
        if (countdown % 7 == 1 && countdown < 22)
            pixmap.load(".\\src\\countdown\\1.png");  // mutual pic (head 1
        else if (countdown % 7 == 2 && countdown < 22)
            pixmap.load(".\\src\\countdown\\2.png");  // mutual pic (head 2
        else if ((countdown % 7 == 5 || countdown % 7 == 6) && countdown < 22)
            pixmap.load(".\\src\\countdown\\0.png");  // mutual pic (body
        else if (countdown % 7 == 0 && countdown < 22)
            pixmap.load(".\\src\\countdown\\5.png");  // mutual pic (last
        else if (countdown == 3)
            pixmap.load(".\\src\\countdown\\31.png");  // count 3
        else if (countdown == 4)
            pixmap.load(".\\src\\countdown\\32.png");
        else if (countdown == 10)
            pixmap.load(".\\src\\countdown\\21.png");  // count 2
        else if (countdown == 11)
            pixmap.load(".\\src\\countdown\\22.png");
        else if (countdown == 17)
            pixmap.load(".\\src\\countdown\\11.png");  // count 1
        else if (countdown == 18)
            pixmap.load(".\\src\\countdown\\12.png");
        else if (countdown >= 22 && countdown % 2 == 0)
            pixmap.load(".\\src\\capoo_scared\\1.png");  // AAAAAAHHHHHHHHHHH
        else if (countdown >= 23 && countdown % 2 == 1)
            pixmap.load(".\\src\\capoo_scared\\2.png");  // AAAAAAHHHHHHHHHHH
        countdown++;

        painter.drawPixmap(0, 0, pixmap);
    }

    // gaming window
    else if (window == 1) {
        //delete the timer and create a new one
        killTimer(timer);
        timer = startTimer(frequency);

        // background pic
        pixmap.load(".\\src\\background\\XP_plus.png");
        painter.drawPixmap(0, 0, pixmap);

        // layout grass
        pixmap.load(".\\src\\grass\\9.png");
        //painter.drawPixmap(obstacle_table[1][9][0], obstacle_table[1][9][1], pixmap);
        for (int i = 0; i < 5; i++) {
            if (*(&row9.send() + i) == 0) {
                painter.drawPixmap(obstacle_table[i][9][0], obstacle_table[i][9][1], pixmap);
            }
        }
        pixmap.load(".\\src\\grass\\8.png");
        //painter.drawPixmap(obstacle_table[0][8][0], obstacle_table[0][8][1], pixmap);
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
        //painter.drawPixmap(obstacle_table[3][5][0], obstacle_table[3][5][1], pixmap);
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
        pixmap.load(".\\src\\grass\\0.png");
        for (int i = 0; i < 5; i++) {
            if (*(&row0.send() + i) == 0) {
                painter.drawPixmap(obstacle_table[i][0][0], obstacle_table[i][0][1], pixmap);
            }
        }

        // capoo gif
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

        capoo++;
        if (capoo > 6) capoo = 1;
        painter.drawPixmap(250 * pos - 50, 425, pixmap);  // 400 320 -> 450 370
    }
}

void RunCapooRun::mouseReleaseEvent(QMouseEvent* evt) {
    repaint();
    //　start button pressed
    if (!window) {
        QPoint point = evt->pos();
        if ((point.x() > 450 && point.x() < 750) && (point.y() > 470 && point.y() < 550)) startClick = (!startClick);
    } else {
        if (evt->button() == Qt::LeftButton && pos > 0)
            pos--;
        else if (evt->button() == Qt::RightButton && pos < 4)
            pos++;
    }
    repaint();
}

void RunCapooRun::timerEvent(QTimerEvent* evt) {
    repaint();  //refresh

    movingTimer++;  // count to 1 sec, per "movingTimer" is a "100 micro sec"

    // when it accumulates to 1 sec, reset the counter and push the map
    if (movingTimer == 10) {
        movingTimer = 0;  //reset
        create_counter++;
        if (frequency > 0) frequency -= 1;  // let game getting faster

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
        } else
            row9.reset();  // 輸出空行
    }
}

void RunCapooRun::setObsTable() {
    // key ( x, y in pixel) into (x, y in coordinate plane)
    //1
    for (int i = 0; i < 5; i++) {
        obstacle_table[i][1][1] = 465;
    }
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
