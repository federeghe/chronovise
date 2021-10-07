#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QLineSeries>
#include <QMainWindow>
#include <iostream>
#include <qradiobutton.h>



QT_BEGIN_NAMESPACE

using namespace QtCharts;
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

//template<typename T>
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();





private slots:
    void on_pb_open_input_clicked();

    void on_pb_reset_clicked();


private:
    Ui::MainWindow *ui;


};
#endif // MAINWINDOW_H
