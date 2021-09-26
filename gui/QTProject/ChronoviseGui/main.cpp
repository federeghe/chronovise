#include "mainwindow.h"
#include <QApplication>
#include <model.h>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Model* model=new Model();
    MainWindow controller(nullptr, model);
    controller.show();
    return a.exec();
}
