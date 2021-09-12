#include "mainwindow.h"
#include <QApplication>
#include <model.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model* m = new Model();
    MainWindow *w = new MainWindow(nullptr, m);
    w->show();
    return a.exec();
}
