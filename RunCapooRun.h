#pragma once

#include <QtWidgets/QMainWindow>
#include "grass.h"
#include "ui_RunCapooRun.h"

class RunCapooRun : public QMainWindow {
    Q_OBJECT

  public:
    RunCapooRun(QWidget* parent = Q_NULLPTR);

    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent* evt);
    void timerEvent(QTimerEvent* evt);
    void setObsTable();

  private:
    Ui::RunCapooRunClass ui;

    bool startClick;                                                   // click of the start botton
    int window;                                                        // main window : 0, game window : 1
    int pos;                                                           // capoo's position (0~4), x = 225  ps.the (center, bottom) of the window is (600, 720)
    int capoo;                                                         // capoo's status
    int timer;                                                         // initial timer
    int countdown;                                                     // for countdown window usage
    int movingTimer;                                                   // counting time (1 time per second
    float frequency;                                                   // initial frequency
    int create_counter;                                                // 值為 0 的時候生成障礙物， 其餘時候生成空行
    grass row0, row1, row2, row3, row4, row5, row6, row7, row8, row9;  // 玩家位置在 row0
    int obstacle_table[5][10][2];                                      //[coordinate x][coordinate y][pix x, pix y]
    int ending_counter;                                                //for layouting ending window usage
};
