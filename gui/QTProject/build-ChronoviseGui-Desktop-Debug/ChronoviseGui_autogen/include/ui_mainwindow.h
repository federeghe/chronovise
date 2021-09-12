/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.8
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QLabel *logo_lbl;
    QLabel *title_lbl;
    QGroupBox *plot_config_gb;
    QRadioButton *linear_rb;
    QRadioButton *log_rb;
    QLabel *y_scale_lbl;
    QPushButton *reset_button;
    QTabWidget *plot_tab;
    QCustomPlot *pdf;
    QCustomPlot *cdf;
    QCustomPlot *ccdf;
    QPushButton *input_file_button;
    QPushButton *compute_button;
    QGroupBox *plot_config_2;
    QLabel *y_scale_lbl_2;
    QRadioButton *linear_rb_2;
    QRadioButton *log_rb_2;
    QGroupBox *config_gb;
    QComboBox *test3_cb;
    QLabel *iid_test_lbl;
    QComboBox *comboBox;
    QComboBox *sig_lev_cb_2;
    QLabel *evt_approach_lbl;
    QComboBox *test1_cb;
    QComboBox *gof_test_cb;
    QLabel *test2_lbl;
    QLabel *test1_lbl;
    QLabel *sig_lev_lbl;
    QComboBox *sig_lev_cb_4;
    QLabel *evt_estimator_lbl;
    QComboBox *comboBox_3;
    QComboBox *test2_cb;
    QLabel *test3_lbl;
    QComboBox *sig_lev_cb_3;
    QLabel *gof_test_lbl;
    QLabel *trend_kpss_lbl;
    QComboBox *evt_approach_cb;
    QComboBox *sig_lev_cb_1;
    QComboBox *comboBox_2;
    QComboBox *evt_estimator_cb;
    QGroupBox *plot_config_3;
    QLabel *y_scale_lbl_3;
    QRadioButton *linear_rb_3;
    QRadioButton *log_rb_3;
    QGroupBox *result_gb;
    QLabel *test1_res_lbl;
    QLabel *test2_res_lbl;
    QLabel *test_res_lbl;
    QLabel *output_lbl;
    QLabel *test1_output_lbl;
    QLabel *test2_output_lbl;
    QLabel *test3_output_lbl;
    QLabel *critical_value_lbl;
    QLabel *test1_c_v_lbl;
    QLabel *test2_c_v_lbl;
    QLabel *test3_c_v_lbl;
    QLabel *statistic_lbl;
    QLabel *test1_st_lbl;
    QLabel *test2_st_lbl;
    QLabel *test3_st_lbl;
    QLabel *w_case_lbl;
    QLabel *lbl_res_pwcet_103_lbl;
    QLabel *lbl_res_pwcet_109_lbl;
    QLabel *lbl_res_pwcet_103;
    QLabel *lbl_res_pwcet_104;
    QLabel *wtime_lbl;
    QLabel *gof_test_result_lbl;
    QLabel *gof_ouput_lbl;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1449, 1161);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color:#EEF;\n"
"selection-background-color: qlineargradient(spread:pad, x1:0, y1:0, x2:1, y2:0, stop:0 rgba(0, 0, 0, 255), stop:1 rgba(255, 255, 255, 255));"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        logo_lbl = new QLabel(centralwidget);
        logo_lbl->setObjectName(QString::fromUtf8("logo_lbl"));
        logo_lbl->setMinimumSize(QSize(20, 20));
        logo_lbl->setMaximumSize(QSize(100, 100));
        logo_lbl->setPixmap(QPixmap(QString::fromUtf8(":/logos/logo.svg")));
        logo_lbl->setScaledContents(true);

        gridLayout->addWidget(logo_lbl, 0, 0, 1, 1);

        title_lbl = new QLabel(centralwidget);
        title_lbl->setObjectName(QString::fromUtf8("title_lbl"));
        QFont font;
        font.setFamily(QString::fromUtf8("Ubuntu Condensed"));
        font.setPointSize(50);
        font.setBold(true);
        font.setWeight(75);
        title_lbl->setFont(font);
        title_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(title_lbl, 0, 1, 1, 2);

        plot_config_gb = new QGroupBox(centralwidget);
        plot_config_gb->setObjectName(QString::fromUtf8("plot_config_gb"));
        plot_config_gb->setMinimumSize(QSize(310, 0));
        plot_config_gb->setMaximumSize(QSize(16777215, 100));
        QFont font1;
        font1.setPointSize(13);
        plot_config_gb->setFont(font1);
        linear_rb = new QRadioButton(plot_config_gb);
        linear_rb->setObjectName(QString::fromUtf8("linear_rb"));
        linear_rb->setGeometry(QRect(110, 55, 68, 23));
        log_rb = new QRadioButton(plot_config_gb);
        log_rb->setObjectName(QString::fromUtf8("log_rb"));
        log_rb->setGeometry(QRect(193, 55, 106, 23));
        y_scale_lbl = new QLabel(plot_config_gb);
        y_scale_lbl->setObjectName(QString::fromUtf8("y_scale_lbl"));
        y_scale_lbl->setGeometry(QRect(12, 55, 84, 17));
        y_scale_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(plot_config_gb, 6, 0, 1, 1);

        reset_button = new QPushButton(centralwidget);
        reset_button->setObjectName(QString::fromUtf8("reset_button"));
        reset_button->setMaximumSize(QSize(120, 16777215));
        reset_button->setFont(font1);

        gridLayout->addWidget(reset_button, 3, 1, 1, 1);

        plot_tab = new QTabWidget(centralwidget);
        plot_tab->setObjectName(QString::fromUtf8("plot_tab"));
        plot_tab->setFocusPolicy(Qt::TabFocus);
        pdf = new QCustomPlot();
        pdf->setObjectName(QString::fromUtf8("pdf"));
        plot_tab->addTab(pdf, QString());
        cdf = new QCustomPlot();
        cdf->setObjectName(QString::fromUtf8("cdf"));
        plot_tab->addTab(cdf, QString());
        ccdf = new QCustomPlot();
        ccdf->setObjectName(QString::fromUtf8("ccdf"));
        plot_tab->addTab(ccdf, QString());

        gridLayout->addWidget(plot_tab, 6, 1, 4, 3);

        input_file_button = new QPushButton(centralwidget);
        input_file_button->setObjectName(QString::fromUtf8("input_file_button"));
        input_file_button->setFont(font1);

        gridLayout->addWidget(input_file_button, 1, 0, 1, 1);

        compute_button = new QPushButton(centralwidget);
        compute_button->setObjectName(QString::fromUtf8("compute_button"));
        compute_button->setMaximumSize(QSize(120, 16777215));
        compute_button->setFont(font1);

        gridLayout->addWidget(compute_button, 3, 0, 1, 1);

        plot_config_2 = new QGroupBox(centralwidget);
        plot_config_2->setObjectName(QString::fromUtf8("plot_config_2"));
        plot_config_2->setMaximumSize(QSize(16777215, 100));
        plot_config_2->setFont(font1);
        y_scale_lbl_2 = new QLabel(plot_config_2);
        y_scale_lbl_2->setObjectName(QString::fromUtf8("y_scale_lbl_2"));
        y_scale_lbl_2->setGeometry(QRect(12, 55, 84, 17));
        linear_rb_2 = new QRadioButton(plot_config_2);
        linear_rb_2->setObjectName(QString::fromUtf8("linear_rb_2"));
        linear_rb_2->setGeometry(QRect(110, 55, 68, 23));
        log_rb_2 = new QRadioButton(plot_config_2);
        log_rb_2->setObjectName(QString::fromUtf8("log_rb_2"));
        log_rb_2->setGeometry(QRect(190, 55, 112, 23));

        gridLayout->addWidget(plot_config_2, 7, 0, 1, 1);

        config_gb = new QGroupBox(centralwidget);
        config_gb->setObjectName(QString::fromUtf8("config_gb"));
        config_gb->setMaximumSize(QSize(730, 270));
        config_gb->setFont(font1);
        test3_cb = new QComboBox(config_gb);
        test3_cb->addItem(QString());
        test3_cb->addItem(QString());
        test3_cb->addItem(QString());
        test3_cb->addItem(QString());
        test3_cb->addItem(QString());
        test3_cb->setObjectName(QString::fromUtf8("test3_cb"));
        test3_cb->setGeometry(QRect(119, 120, 272, 25));
        iid_test_lbl = new QLabel(config_gb);
        iid_test_lbl->setObjectName(QString::fromUtf8("iid_test_lbl"));
        iid_test_lbl->setGeometry(QRect(12, 35, 93, 17));
        comboBox = new QComboBox(config_gb);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(593, 58, 69, 25));
        sig_lev_cb_2 = new QComboBox(config_gb);
        sig_lev_cb_2->addItem(QString());
        sig_lev_cb_2->addItem(QString());
        sig_lev_cb_2->addItem(QString());
        sig_lev_cb_2->setObjectName(QString::fromUtf8("sig_lev_cb_2"));
        sig_lev_cb_2->setGeometry(QRect(480, 89, 58, 25));
        evt_approach_lbl = new QLabel(config_gb);
        evt_approach_lbl->setObjectName(QString::fromUtf8("evt_approach_lbl"));
        evt_approach_lbl->setGeometry(QRect(12, 182, 100, 17));
        test1_cb = new QComboBox(config_gb);
        test1_cb->addItem(QString());
        test1_cb->addItem(QString());
        test1_cb->addItem(QString());
        test1_cb->addItem(QString());
        test1_cb->addItem(QString());
        test1_cb->setObjectName(QString::fromUtf8("test1_cb"));
        test1_cb->setGeometry(QRect(119, 58, 272, 25));
        test1_cb->setLayoutDirection(Qt::LeftToRight);
        test1_cb->setAutoFillBackground(false);
        gof_test_cb = new QComboBox(config_gb);
        gof_test_cb->addItem(QString());
        gof_test_cb->addItem(QString());
        gof_test_cb->addItem(QString());
        gof_test_cb->addItem(QString());
        gof_test_cb->addItem(QString());
        gof_test_cb->setObjectName(QString::fromUtf8("gof_test_cb"));
        gof_test_cb->setGeometry(QRect(119, 151, 215, 25));
        test2_lbl = new QLabel(config_gb);
        test2_lbl->setObjectName(QString::fromUtf8("test2_lbl"));
        test2_lbl->setGeometry(QRect(20, 90, 57, 18));
        test1_lbl = new QLabel(config_gb);
        test1_lbl->setObjectName(QString::fromUtf8("test1_lbl"));
        test1_lbl->setGeometry(QRect(20, 60, 57, 18));
        sig_lev_lbl = new QLabel(config_gb);
        sig_lev_lbl->setObjectName(QString::fromUtf8("sig_lev_lbl"));
        sig_lev_lbl->setGeometry(QRect(459, 35, 128, 17));
        sig_lev_cb_4 = new QComboBox(config_gb);
        sig_lev_cb_4->addItem(QString());
        sig_lev_cb_4->addItem(QString());
        sig_lev_cb_4->addItem(QString());
        sig_lev_cb_4->setObjectName(QString::fromUtf8("sig_lev_cb_4"));
        sig_lev_cb_4->setGeometry(QRect(480, 151, 58, 25));
        evt_estimator_lbl = new QLabel(config_gb);
        evt_estimator_lbl->setObjectName(QString::fromUtf8("evt_estimator_lbl"));
        evt_estimator_lbl->setGeometry(QRect(12, 213, 101, 17));
        comboBox_3 = new QComboBox(config_gb);
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->addItem(QString());
        comboBox_3->setObjectName(QString::fromUtf8("comboBox_3"));
        comboBox_3->setGeometry(QRect(593, 120, 69, 25));
        test2_cb = new QComboBox(config_gb);
        test2_cb->addItem(QString());
        test2_cb->addItem(QString());
        test2_cb->addItem(QString());
        test2_cb->addItem(QString());
        test2_cb->addItem(QString());
        test2_cb->setObjectName(QString::fromUtf8("test2_cb"));
        test2_cb->setGeometry(QRect(119, 89, 272, 25));
        test3_lbl = new QLabel(config_gb);
        test3_lbl->setObjectName(QString::fromUtf8("test3_lbl"));
        test3_lbl->setGeometry(QRect(20, 120, 57, 18));
        sig_lev_cb_3 = new QComboBox(config_gb);
        sig_lev_cb_3->addItem(QString());
        sig_lev_cb_3->addItem(QString());
        sig_lev_cb_3->addItem(QString());
        sig_lev_cb_3->setObjectName(QString::fromUtf8("sig_lev_cb_3"));
        sig_lev_cb_3->setGeometry(QRect(480, 120, 58, 25));
        gof_test_lbl = new QLabel(config_gb);
        gof_test_lbl->setObjectName(QString::fromUtf8("gof_test_lbl"));
        gof_test_lbl->setGeometry(QRect(12, 151, 63, 17));
        trend_kpss_lbl = new QLabel(config_gb);
        trend_kpss_lbl->setObjectName(QString::fromUtf8("trend_kpss_lbl"));
        trend_kpss_lbl->setGeometry(QRect(593, 35, 82, 17));
        trend_kpss_lbl->setAlignment(Qt::AlignCenter);
        evt_approach_cb = new QComboBox(config_gb);
        evt_approach_cb->addItem(QString());
        evt_approach_cb->addItem(QString());
        evt_approach_cb->addItem(QString());
        evt_approach_cb->setObjectName(QString::fromUtf8("evt_approach_cb"));
        evt_approach_cb->setGeometry(QRect(119, 182, 169, 25));
        sig_lev_cb_1 = new QComboBox(config_gb);
        sig_lev_cb_1->addItem(QString());
        sig_lev_cb_1->addItem(QString());
        sig_lev_cb_1->addItem(QString());
        sig_lev_cb_1->setObjectName(QString::fromUtf8("sig_lev_cb_1"));
        sig_lev_cb_1->setGeometry(QRect(480, 58, 58, 25));
        comboBox_2 = new QComboBox(config_gb);
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->addItem(QString());
        comboBox_2->setObjectName(QString::fromUtf8("comboBox_2"));
        comboBox_2->setGeometry(QRect(593, 89, 69, 25));
        evt_estimator_cb = new QComboBox(config_gb);
        evt_estimator_cb->addItem(QString());
        evt_estimator_cb->addItem(QString());
        evt_estimator_cb->addItem(QString());
        evt_estimator_cb->addItem(QString());
        evt_estimator_cb->setObjectName(QString::fromUtf8("evt_estimator_cb"));
        evt_estimator_cb->setGeometry(QRect(119, 213, 334, 25));

        gridLayout->addWidget(config_gb, 2, 0, 1, 3);

        plot_config_3 = new QGroupBox(centralwidget);
        plot_config_3->setObjectName(QString::fromUtf8("plot_config_3"));
        plot_config_3->setMaximumSize(QSize(16777215, 100));
        plot_config_3->setFont(font1);
        y_scale_lbl_3 = new QLabel(plot_config_3);
        y_scale_lbl_3->setObjectName(QString::fromUtf8("y_scale_lbl_3"));
        y_scale_lbl_3->setGeometry(QRect(12, 55, 84, 17));
        linear_rb_3 = new QRadioButton(plot_config_3);
        linear_rb_3->setObjectName(QString::fromUtf8("linear_rb_3"));
        linear_rb_3->setGeometry(QRect(110, 55, 68, 23));
        log_rb_3 = new QRadioButton(plot_config_3);
        log_rb_3->setObjectName(QString::fromUtf8("log_rb_3"));
        log_rb_3->setGeometry(QRect(190, 55, 112, 23));

        gridLayout->addWidget(plot_config_3, 8, 0, 1, 1);

        result_gb = new QGroupBox(centralwidget);
        result_gb->setObjectName(QString::fromUtf8("result_gb"));
        result_gb->setMinimumSize(QSize(500, 350));
        result_gb->setMaximumSize(QSize(400, 16777215));
        result_gb->setFont(font1);
        result_gb->setCursor(QCursor(Qt::ArrowCursor));
        result_gb->setMouseTracking(false);
        test1_res_lbl = new QLabel(result_gb);
        test1_res_lbl->setObjectName(QString::fromUtf8("test1_res_lbl"));
        test1_res_lbl->setGeometry(QRect(12, 76, 45, 17));
        test1_res_lbl->setAlignment(Qt::AlignCenter);
        test2_res_lbl = new QLabel(result_gb);
        test2_res_lbl->setObjectName(QString::fromUtf8("test2_res_lbl"));
        test2_res_lbl->setGeometry(QRect(12, 118, 48, 17));
        test2_res_lbl->setAlignment(Qt::AlignCenter);
        test_res_lbl = new QLabel(result_gb);
        test_res_lbl->setObjectName(QString::fromUtf8("test_res_lbl"));
        test_res_lbl->setGeometry(QRect(12, 159, 48, 17));
        test_res_lbl->setAlignment(Qt::AlignCenter);
        output_lbl = new QLabel(result_gb);
        output_lbl->setObjectName(QString::fromUtf8("output_lbl"));
        output_lbl->setGeometry(QRect(369, 35, 90, 17));
        output_lbl->setAlignment(Qt::AlignCenter);
        test1_output_lbl = new QLabel(result_gb);
        test1_output_lbl->setObjectName(QString::fromUtf8("test1_output_lbl"));
        test1_output_lbl->setGeometry(QRect(369, 76, 90, 36));
        test1_output_lbl->setAlignment(Qt::AlignCenter);
        test2_output_lbl = new QLabel(result_gb);
        test2_output_lbl->setObjectName(QString::fromUtf8("test2_output_lbl"));
        test2_output_lbl->setGeometry(QRect(369, 118, 90, 35));
        test2_output_lbl->setAlignment(Qt::AlignCenter);
        test3_output_lbl = new QLabel(result_gb);
        test3_output_lbl->setObjectName(QString::fromUtf8("test3_output_lbl"));
        test3_output_lbl->setGeometry(QRect(369, 159, 90, 36));
        test3_output_lbl->setAlignment(Qt::AlignCenter);
        critical_value_lbl = new QLabel(result_gb);
        critical_value_lbl->setObjectName(QString::fromUtf8("critical_value_lbl"));
        critical_value_lbl->setGeometry(QRect(272, 35, 90, 17));
        critical_value_lbl->setAlignment(Qt::AlignCenter);
        test1_c_v_lbl = new QLabel(result_gb);
        test1_c_v_lbl->setObjectName(QString::fromUtf8("test1_c_v_lbl"));
        test1_c_v_lbl->setGeometry(QRect(272, 76, 91, 36));
        test1_c_v_lbl->setAlignment(Qt::AlignCenter);
        test2_c_v_lbl = new QLabel(result_gb);
        test2_c_v_lbl->setObjectName(QString::fromUtf8("test2_c_v_lbl"));
        test2_c_v_lbl->setGeometry(QRect(272, 118, 91, 35));
        test2_c_v_lbl->setAlignment(Qt::AlignCenter);
        test3_c_v_lbl = new QLabel(result_gb);
        test3_c_v_lbl->setObjectName(QString::fromUtf8("test3_c_v_lbl"));
        test3_c_v_lbl->setGeometry(QRect(272, 159, 91, 36));
        test3_c_v_lbl->setAlignment(Qt::AlignCenter);
        statistic_lbl = new QLabel(result_gb);
        statistic_lbl->setObjectName(QString::fromUtf8("statistic_lbl"));
        statistic_lbl->setGeometry(QRect(186, 35, 62, 17));
        statistic_lbl->setAlignment(Qt::AlignCenter);
        test1_st_lbl = new QLabel(result_gb);
        test1_st_lbl->setObjectName(QString::fromUtf8("test1_st_lbl"));
        test1_st_lbl->setGeometry(QRect(176, 76, 90, 36));
        test1_st_lbl->setAlignment(Qt::AlignCenter);
        test2_st_lbl = new QLabel(result_gb);
        test2_st_lbl->setObjectName(QString::fromUtf8("test2_st_lbl"));
        test2_st_lbl->setGeometry(QRect(176, 118, 90, 35));
        test2_st_lbl->setAlignment(Qt::AlignCenter);
        test3_st_lbl = new QLabel(result_gb);
        test3_st_lbl->setObjectName(QString::fromUtf8("test3_st_lbl"));
        test3_st_lbl->setGeometry(QRect(176, 159, 90, 36));
        test3_st_lbl->setAlignment(Qt::AlignCenter);
        w_case_lbl = new QLabel(result_gb);
        w_case_lbl->setObjectName(QString::fromUtf8("w_case_lbl"));
        w_case_lbl->setGeometry(QRect(10, 250, 150, 17));
        w_case_lbl->setAlignment(Qt::AlignCenter);
        lbl_res_pwcet_103_lbl = new QLabel(result_gb);
        lbl_res_pwcet_103_lbl->setObjectName(QString::fromUtf8("lbl_res_pwcet_103_lbl"));
        lbl_res_pwcet_103_lbl->setGeometry(QRect(10, 280, 156, 17));
        lbl_res_pwcet_103_lbl->setAlignment(Qt::AlignCenter);
        lbl_res_pwcet_109_lbl = new QLabel(result_gb);
        lbl_res_pwcet_109_lbl->setObjectName(QString::fromUtf8("lbl_res_pwcet_109_lbl"));
        lbl_res_pwcet_109_lbl->setGeometry(QRect(10, 320, 158, 17));
        lbl_res_pwcet_109_lbl->setAlignment(Qt::AlignCenter);
        lbl_res_pwcet_103 = new QLabel(result_gb);
        lbl_res_pwcet_103->setObjectName(QString::fromUtf8("lbl_res_pwcet_103"));
        lbl_res_pwcet_103->setGeometry(QRect(180, 270, 90, 35));
        lbl_res_pwcet_103->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        lbl_res_pwcet_104 = new QLabel(result_gb);
        lbl_res_pwcet_104->setObjectName(QString::fromUtf8("lbl_res_pwcet_104"));
        lbl_res_pwcet_104->setGeometry(QRect(180, 310, 90, 35));
        lbl_res_pwcet_104->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        wtime_lbl = new QLabel(result_gb);
        wtime_lbl->setObjectName(QString::fromUtf8("wtime_lbl"));
        wtime_lbl->setGeometry(QRect(180, 240, 90, 35));
        gof_test_result_lbl = new QLabel(result_gb);
        gof_test_result_lbl->setObjectName(QString::fromUtf8("gof_test_result_lbl"));
        gof_test_result_lbl->setGeometry(QRect(12, 210, 67, 17));
        gof_ouput_lbl = new QLabel(result_gb);
        gof_ouput_lbl->setObjectName(QString::fromUtf8("gof_ouput_lbl"));
        gof_ouput_lbl->setGeometry(QRect(369, 200, 90, 36));
        gof_ouput_lbl->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(result_gb, 1, 3, 3, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        plot_tab->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        logo_lbl->setText(QString());
        title_lbl->setText(QApplication::translate("MainWindow", "Chronovise", nullptr));
        plot_config_gb->setTitle(QApplication::translate("MainWindow", "Plot Configuration PDF", nullptr));
        linear_rb->setText(QApplication::translate("MainWindow", "Linear", nullptr));
        log_rb->setText(QApplication::translate("MainWindow", "Logarithmic ", nullptr));
        y_scale_lbl->setText(QApplication::translate("MainWindow", "Y-Axis Scale:", nullptr));
        reset_button->setText(QApplication::translate("MainWindow", "Reset", nullptr));
        plot_tab->setTabText(plot_tab->indexOf(pdf), QApplication::translate("MainWindow", "PDF", nullptr));
        plot_tab->setTabText(plot_tab->indexOf(cdf), QApplication::translate("MainWindow", "CDF", nullptr));
        plot_tab->setTabText(plot_tab->indexOf(ccdf), QApplication::translate("MainWindow", "CCDF", nullptr));
        input_file_button->setText(QApplication::translate("MainWindow", "Open Input File", nullptr));
        compute_button->setText(QApplication::translate("MainWindow", "Compute", nullptr));
        plot_config_2->setTitle(QApplication::translate("MainWindow", "Plot Configuration CDF", nullptr));
        y_scale_lbl_2->setText(QApplication::translate("MainWindow", "Y-Axis Scale:", nullptr));
        linear_rb_2->setText(QApplication::translate("MainWindow", "Linear", nullptr));
        log_rb_2->setText(QApplication::translate("MainWindow", "Logarithmic ", nullptr));
        config_gb->setTitle(QApplication::translate("MainWindow", "Configuration", nullptr));
        test3_cb->setItemText(0, QString());
        test3_cb->setItemText(1, QApplication::translate("MainWindow", "Kwiatkowski\342\200\223Phillips\342\200\223Schmidt\342\200\223Shin", nullptr));
        test3_cb->setItemText(2, QApplication::translate("MainWindow", "Brock\342\200\223Dechert\342\200\223Scheinkman", nullptr));
        test3_cb->setItemText(3, QApplication::translate("MainWindow", "LjungBox", nullptr));
        test3_cb->setItemText(4, QApplication::translate("MainWindow", "R/S", nullptr));

        iid_test_lbl->setText(QApplication::translate("MainWindow", "EVT i.i.d. test:", nullptr));
        comboBox->setItemText(0, QString());
        comboBox->setItemText(1, QApplication::translate("MainWindow", "Level", nullptr));
        comboBox->setItemText(2, QApplication::translate("MainWindow", "Trend", nullptr));

        sig_lev_cb_2->setItemText(0, QString());
        sig_lev_cb_2->setItemText(1, QApplication::translate("MainWindow", "0.01", nullptr));
        sig_lev_cb_2->setItemText(2, QApplication::translate("MainWindow", "0.05", nullptr));

        evt_approach_lbl->setText(QApplication::translate("MainWindow", "EVT Approach:", nullptr));
        test1_cb->setItemText(0, QString());
        test1_cb->setItemText(1, QApplication::translate("MainWindow", "Kwiatkowski\342\200\223Phillips\342\200\223Schmidt\342\200\223Shin", nullptr));
        test1_cb->setItemText(2, QApplication::translate("MainWindow", "Brock\342\200\223Dechert\342\200\223Scheinkman", nullptr));
        test1_cb->setItemText(3, QApplication::translate("MainWindow", "LjungBox", nullptr));
        test1_cb->setItemText(4, QApplication::translate("MainWindow", "R/S", nullptr));

        gof_test_cb->setItemText(0, QString());
        gof_test_cb->setItemText(1, QApplication::translate("MainWindow", "Kolmogorov-Smirnov", nullptr));
        gof_test_cb->setItemText(2, QApplication::translate("MainWindow", "Cram\303\251r\342\200\223von Mises", nullptr));
        gof_test_cb->setItemText(3, QApplication::translate("MainWindow", "Anderson-Darling", nullptr));
        gof_test_cb->setItemText(4, QApplication::translate("MainWindow", "Modified Anderson-Darling", nullptr));

        test2_lbl->setText(QApplication::translate("MainWindow", "\342\206\263Test 2:", nullptr));
        test1_lbl->setText(QApplication::translate("MainWindow", "\342\206\263Test 1:", nullptr));
        sig_lev_lbl->setText(QApplication::translate("MainWindow", "Significance Level: ", nullptr));
        sig_lev_cb_4->setItemText(0, QString());
        sig_lev_cb_4->setItemText(1, QApplication::translate("MainWindow", "0.01", nullptr));
        sig_lev_cb_4->setItemText(2, QApplication::translate("MainWindow", "0.05", nullptr));

        evt_estimator_lbl->setText(QApplication::translate("MainWindow", "EVT Estimator:", nullptr));
        comboBox_3->setItemText(0, QString());
        comboBox_3->setItemText(1, QApplication::translate("MainWindow", "Level", nullptr));
        comboBox_3->setItemText(2, QApplication::translate("MainWindow", "Trend", nullptr));

        test2_cb->setItemText(0, QString());
        test2_cb->setItemText(1, QApplication::translate("MainWindow", "Kwiatkowski\342\200\223Phillips\342\200\223Schmidt\342\200\223Shin", nullptr));
        test2_cb->setItemText(2, QApplication::translate("MainWindow", "Brock\342\200\223Dechert\342\200\223Scheinkman", nullptr));
        test2_cb->setItemText(3, QApplication::translate("MainWindow", "LjungBox", nullptr));
        test2_cb->setItemText(4, QApplication::translate("MainWindow", "R/S", nullptr));

        test3_lbl->setText(QApplication::translate("MainWindow", "\342\206\263Test 3:", nullptr));
        sig_lev_cb_3->setItemText(0, QString());
        sig_lev_cb_3->setItemText(1, QApplication::translate("MainWindow", "0.01", nullptr));
        sig_lev_cb_3->setItemText(2, QApplication::translate("MainWindow", "0.05", nullptr));

        gof_test_lbl->setText(QApplication::translate("MainWindow", "GoF Test:", nullptr));
        trend_kpss_lbl->setText(QApplication::translate("MainWindow", "Trend Class:", nullptr));
        evt_approach_cb->setItemText(0, QString());
        evt_approach_cb->setItemText(1, QApplication::translate("MainWindow", "Block-Maxima", nullptr));
        evt_approach_cb->setItemText(2, QApplication::translate("MainWindow", "Peak-over-Threshold", nullptr));

        sig_lev_cb_1->setItemText(0, QString());
        sig_lev_cb_1->setItemText(1, QApplication::translate("MainWindow", "0.01", nullptr));
        sig_lev_cb_1->setItemText(2, QApplication::translate("MainWindow", "0.05", nullptr));

        comboBox_2->setItemText(0, QString());
        comboBox_2->setItemText(1, QApplication::translate("MainWindow", "Level", nullptr));
        comboBox_2->setItemText(2, QApplication::translate("MainWindow", "Trend", nullptr));

        evt_estimator_cb->setItemText(0, QString());
        evt_estimator_cb->setItemText(1, QApplication::translate("MainWindow", "Probability Weighted Moments", nullptr));
        evt_estimator_cb->setItemText(2, QApplication::translate("MainWindow", "Maximum Likelihood Estimation", nullptr));
        evt_estimator_cb->setItemText(3, QApplication::translate("MainWindow", "Generalized Maximum Likelihood Estimation", nullptr));

        plot_config_3->setTitle(QApplication::translate("MainWindow", "Plot Configuration CCDF", nullptr));
        y_scale_lbl_3->setText(QApplication::translate("MainWindow", "Y-Axis Scale:", nullptr));
        linear_rb_3->setText(QApplication::translate("MainWindow", "Linear", nullptr));
        log_rb_3->setText(QApplication::translate("MainWindow", "Logarithmic ", nullptr));
        result_gb->setTitle(QApplication::translate("MainWindow", "Results", nullptr));
        test1_res_lbl->setText(QApplication::translate("MainWindow", "Test 1:", nullptr));
        test2_res_lbl->setText(QApplication::translate("MainWindow", "Test 2: ", nullptr));
        test_res_lbl->setText(QApplication::translate("MainWindow", "Test 3: ", nullptr));
        output_lbl->setText(QApplication::translate("MainWindow", "Otput", nullptr));
        test1_output_lbl->setText(QString());
        test2_output_lbl->setText(QString());
        test3_output_lbl->setText(QString());
        critical_value_lbl->setText(QApplication::translate("MainWindow", "Critical Value", nullptr));
        test1_c_v_lbl->setText(QString());
        test2_c_v_lbl->setText(QString());
        test3_c_v_lbl->setText(QString());
        statistic_lbl->setText(QApplication::translate("MainWindow", "Statistics", nullptr));
        test1_st_lbl->setText(QString());
        test2_st_lbl->setText(QString());
        test3_st_lbl->setText(QString());
        w_case_lbl->setText(QApplication::translate("MainWindow", "Worst Observed Case:", nullptr));
        lbl_res_pwcet_103_lbl->setText(QApplication::translate("MainWindow", "pWCET(p=0.999999) is:", nullptr));
        lbl_res_pwcet_109_lbl->setText(QApplication::translate("MainWindow", "pWCET(p=1-10^(-9)) is: ", nullptr));
        lbl_res_pwcet_103->setText(QString());
        lbl_res_pwcet_104->setText(QString());
        wtime_lbl->setText(QString());
        gof_test_result_lbl->setText(QApplication::translate("MainWindow", "GoF Test:", nullptr));
        gof_ouput_lbl->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
