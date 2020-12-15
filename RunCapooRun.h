#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_RunCapooRun.h"

class RunCapooRun : public QMainWindow {
    Q_OBJECT

  public:
    RunCapooRun(QWidget* parent = Q_NULLPTR);

    void paintEvent(QPaintEvent*);
    void mouseReleaseEvent(QMouseEvent* evt);
    void timerEvent(QTimerEvent* evt);

  private:
    Ui::RunCapooRunClass ui;

    bool startClick;
    int window;
    int pos;
    int capoo;
    int timer;
    int countdown;
};
