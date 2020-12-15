#include <QtWidgets/QApplication>
#include "RunCapooRun.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    RunCapooRun window;

    window.setWindowTitle("Run CAPOO Run !!");
    window.setFixedSize(1200, 720);

    window.show();
    return app.exec();
}
