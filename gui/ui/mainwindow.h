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

    void on_pb_compute_clicked();

    void on_bg_funct_plot_buttonClicked(QAbstractButton *button);
    void on_bg_yaxis_plot_buttonClicked(QAbstractButton *button);
    void on_cb_iid_test_currentIndexChanged(int index);

    void on_in_x_scale_min_editingFinished();

    void on_in_x_scale_max_editingFinished();

    void on_pc_about_clicked();

    void on_pb_save_plot_clicked();

private:
    Ui::MainWindow *ui;
    void print_plot(QLineSeries &points, bool log_scale);

};
#endif // MAINWINDOW_H
