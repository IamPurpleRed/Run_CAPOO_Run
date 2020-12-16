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

    startClick = 0;           // click of tthe start botton
    window = 0;               // main window : 0, game window : 1
    pos = 2;                  // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
    capoo = 1;                // capoo's status
    timer = startTimer(100);  // initial timer
    frequency = 100;          // initial frequency
    countdown = 1;            // for countdown window usage
    movingTimer = 0;          // counting time (1 time per second
}

void RunCapooRun::paintEvent(QPaintEvent*) {
    // print window
    QPainter painter(this);
    QPixmap pixmap;
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
        if (countdown > 30) {
            window = 1;    // end countdown
            test_pos = 1;  // test to move objects
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
        timer = startTimer(frequency);  // capoo's timer

        // background pic
        pixmap.load(".\\src\\background\\XP_plus.png");
        painter.drawPixmap(0, 0, pixmap);

        // wall pic
        pixmap.load(".\\src\\grass\\grass1.png");
        painter.drawPixmap(test_pos * 100, 0, pixmap);

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
        movingTimer = 0;
        test_pos++;
        if (frequency > 0) frequency -= 1;  // let game getting faster
    }
}
