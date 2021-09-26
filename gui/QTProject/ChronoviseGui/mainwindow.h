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
    MainWindow(QWidget* parent, Model* model);
    ~MainWindow();
    static int const EXIT_CODE_REBOOT = -123456789;


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



    void on_trend_class_cb_1_currentIndexChanged(int index);

    void on_trend_class_cb_2_currentIndexChanged(int index);

    void on_trend_class_cb_3_currentIndexChanged(int index);

    void on_sig_lev_cb_4_currentIndexChanged(int index);


    void on_log_rb_clicked();

    void on_linear_rb_clicked();

    void on_linear_rb_2_clicked();

    void on_linear_rb_3_clicked();

    void on_log_rb_2_clicked();

    void on_log_rb_3_clicked();

    void on_reset_button_clicked();

    void extend_plot_pdf(const QCPRange &newRange);
    void extend_plot_cdf(const QCPRange &newRange);
    void extend_plot_ccdf(const QCPRange &newRange);




private:
    Ui::MainWindow *ui;
    Model* model;
    void initialize_plot_pdf();
    void initialize_plot_cdf();
    void initialize_plot_ccdf();
    void setup_plot();
    void center_window();
    void clear_lables_and_plots();

};
#endif // MAINWINDOW_H
