#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <model.h>
#include <QLineEdit>
#include <QIntValidator>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent, Model* model);
    ~MainWindow();

private slots:
    void on_input_file_button_clicked();




    void on_test1_cb_currentIndexChanged(int index);

    void on_test2_cb_currentIndexChanged(int index);

    void on_test3_cb_currentIndexChanged(int index);

    void on_compute_button_clicked();

    void on_evt_approach_cb_currentIndexChanged(int index);

    void on_evt_estimator_cb_currentIndexChanged(int index);

    void on_gof_test_cb_currentIndexChanged(int index);

    void on_sig_lev_cb_1_currentIndexChanged(int index);

    void on_sig_lev_cb_2_currentIndexChanged(int index);

    void on_sig_lev_cb_3_currentIndexChanged(int index);







    void on_log_rb_clicked();

    void on_linear_rb_clicked();



    void on_comboBox_currentIndexChanged(int index);

    void on_comboBox_2_currentIndexChanged(int index);

    void on_comboBox_3_currentIndexChanged(int index);

    void on_sig_lev_cb_4_currentIndexChanged(int index);





    void on_linear_rb_2_clicked();

    void on_linear_rb_3_clicked();

    void on_log_rb_2_clicked();

    void on_log_rb_3_clicked();



private:
    Ui::MainWindow *ui;
    Model* model;
    void initialize_plot_pdf(std::shared_ptr<Distribution> distribution);
    void initialize_plot_cdf(std::shared_ptr<Distribution> distribution);
    void initialize_plot_ccdf(std::shared_ptr<Distribution> distribution);
    void setup_plot();
};
#endif // MAINWINDOW_H
