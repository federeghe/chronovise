#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include "utility.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <typeinfo>
#include <QMessageBox>
#include <sstream>
#include <qpixmap.h>
#include <qpixmap.h>
#include <chronovise/evt/gpd_distribution.hpp>
#include <chronovise/measures_pool.hpp>



using namespace chronovise;

std::ifstream input_file;
std::istream *input_s = nullptr;
t_computation_param params;
template<typename D>
t_computation_results<D> results;


//def
template<typename T>
void  fillMeasurePool(chronovise::MeasuresPool<int, T> &mp);

template<typename T>
void generate_pdf(QLineSeries &points, double min, double max, t_computation_results<T> &results);

template<typename T>
void generate_cdf(QLineSeries &points, double min, double max, t_computation_results<T> &results);

template<typename T>
void generate_ccdf(QLineSeries &points, double min, double max, t_computation_results<T> &results);

void reset_results(Ui::MainWindow *ui);


template<typename D, typename T>
void print_results(Ui::MainWindow *ui);

MainWindow::MainWindow(QWidget *parent)

    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //set logo
    QPixmap logo;

    logo.load("../ui/res/logo.svg");
    logo = logo.scaled(70,70);

    ui->lbl_logo->setPixmap(logo);

    // hides progress bar
    ui->pbar_compute->setVisible(false);

    // set save icon
    QPixmap pixmap("../ui/res/save.png");
    QIcon ButtonIcon(pixmap);
    ui->pb_save_plot->setIcon(ButtonIcon);
    ui->pb_save_plot->setIconSize( QSize(25,25));


       // initialize an empty chart
    QChart *chart = new QChart();

    QLineSeries *serie = new QLineSeries();
    chart->createDefaultAxes();
    chart->legend()->hide();


    QAbstractAxis *axisY;

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("WCET");


    chart->addAxis(axisX, Qt::AlignBottom);

    axisY = new  QValueAxis();

    axisY->setTitleText("p");
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(serie);
    serie->attachAxis(axisY);
    serie->attachAxis(axisX);

    ui->chart_view->setChart(chart);
    ui->chart_view->setRenderHint(QPainter::Antialiasing);
    ui->chart_view->setRubberBand(QChartView::HorizontalRubberBand);





}

MainWindow::~MainWindow()
{
    delete ui;
}

/*
 * open file pushbutton clicked event
 */
void MainWindow::on_pb_open_input_clicked()
{

    QString fileName = QFileDialog::getOpenFileName(this,
            tr("Open Initialization File"), "",
            tr("Text File (*.txt);;"));
    input_file.open(fileName.toStdString());
    if(input_file.is_open())
        input_s = &input_file;

}






void MainWindow::on_pb_reset_clicked()
{
    input_file.close();

    input_s = nullptr;

    // clean plot
    ui->chart_view->chart()->removeAllSeries();


    // reset progress bar
    ui->pbar_compute->setValue(0);
    ui->pbar_compute->setVisible(false);

}

template<typename T>
void  fillMeasurePool(chronovise::MeasuresPool<int, T> &mp){

    T value;



    while (*input_s >> value)
    {
        mp.push(0, value);
    }

    if (mp.size() < 20) {
        input_file.close();
        input_s = nullptr;

        throw  std::runtime_error("The sample size is too low.\n Please, upload a new file.");

    }

    input_file.clear();
    input_file.seekg(0);
    input_s = &input_file;



}
void reset_results(Ui::MainWindow *ui){

    ui->lbl_stat_test_ppi->setText("-");
    ui->lbl_cv_test_ppi->setText("-");
    ui->lbl_out_test_ppi->setText( "-" );

    ui->lbl_res_test_1->setText("Test 1:");
    ui->lbl_stat_test_1->setText("-");
    ui->lbl_cv_test_1->setText("-");
    ui->lbl_out_test_1->setText( "-" );

    ui->lbl_res_test_2->setText("Test 2:");
    ui->lbl_stat_test_2->setText("-");
    ui->lbl_cv_test_2->setText("-");
    ui->lbl_out_test_2->setText( "-" );


    ui->lbl_res_test_3->setText("Test 3:");
    ui->lbl_stat_test_3->setText("-");
    ui->lbl_cv_test_3->setText("-");
    ui->lbl_out_test_3->setText( "-" );

    ui->lbl_stat_gof->setText("-");
    ui->lbl_cv_gof->setText("-");
    ui->lbl_out_gof->setText( "-" );

    ui->lbl_res_dist->setText("-");
    ui->lbl_res_location->setText("-");
    ui->lbl_res_scale->setText( "-" );
    ui->lbl_res_shape->setText("-");
    ui->lbl_res_pwcet_103->setText("-");
    ui->lbl_res_pwcet_109->setText( "-" );
}




template<typename D, typename T>
void print_results(Ui::MainWindow *ui){


    reset_results(ui);

    // Create an output string stream
    std::ostringstream streamObj;


    switch(params.iid_t){
        case PPI:{

            //ppi
            streamObj << results<T>.ppi.first;
            ui->lbl_stat_test_ppi->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            streamObj << results<T>.ppi.second;
            ui->lbl_cv_test_ppi->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            if (results<T>.ppi.first > results<T>.ppi.second){
                ui->lbl_out_test_ppi->setText( "FAIL" );
                ui->lbl_out_test_ppi->setStyleSheet("color:red");
            }else{
                ui->lbl_out_test_ppi->setText( "PASS" );
                ui->lbl_out_test_ppi->setStyleSheet("color:green");

            }

            //kpss
            ui->lbl_res_test_1->setText("KPSS: ");
            streamObj << results<T>.test_1.first;
            ui->lbl_stat_test_1->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            streamObj << results<T>.test_1.second;
            ui->lbl_cv_test_1->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            if (results<T>.test_1.first > results<T>.test_1.second){
                ui->lbl_out_test_1->setText( "FAIL" );
                ui->lbl_out_test_1->setStyleSheet("color:red");
            }else{
                ui->lbl_out_test_1->setText( "PASS" );
                ui->lbl_out_test_1->setStyleSheet("color:green");

            }


            // bds
            ui->lbl_res_test_2->setText("BDS:");
            streamObj << results<T>.test_2.first;
            ui->lbl_stat_test_2->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            streamObj << results<T>.test_2.second;
            ui->lbl_cv_test_2->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            if (results<T>.test_2.first > results<T>.test_2.second){
                ui->lbl_out_test_2->setText( "FAIL" );
                ui->lbl_out_test_2->setStyleSheet("color:red");
            }else{
                ui->lbl_out_test_2->setText( "PASS" );
                ui->lbl_out_test_2->setStyleSheet("color:green");

            }

            //rs
            ui->lbl_res_test_3->setText("RS:");
            streamObj << results<T>.test_3.first;
            ui->lbl_stat_test_3->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            streamObj << results<T>.test_3.second;
            ui->lbl_cv_test_3->setText(QString::fromStdString(streamObj.str()));
            streamObj.str("");

            if (results<T>.test_3.first > results<T>.test_3.second){
                ui->lbl_out_test_3->setText( "FAIL" );
                ui->lbl_out_test_3->setStyleSheet("color:red");
            }else{
                ui->lbl_out_test_3->setText( "PASS" );
                ui->lbl_out_test_3->setStyleSheet("color:green");

            }

            }
            break;
        case Custom:{
            if(params.tests[0] != end){
                streamObj << results<T>.test_1.first;
                ui->lbl_stat_test_1->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                streamObj << results<T>.test_1.second;
                ui->lbl_cv_test_1->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                if (results<T>.test_1.first > results<T>.test_1.second){
                    ui->lbl_out_test_1->setText( "FAIL" );
                    ui->lbl_out_test_1->setStyleSheet("color:red");
                }else{
                    ui->lbl_out_test_1->setText( "PASS" );
                    ui->lbl_out_test_1->setStyleSheet("color:green");

                }

            }

            if(params.tests[1] != end){
                streamObj << results<T>.test_2.first;
                ui->lbl_stat_test_2->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                streamObj << results<T>.test_2.second;
                ui->lbl_cv_test_2->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                if (results<T>.test_2.first > results<T>.test_2.second){
                    ui->lbl_out_test_2->setText( "FAIL" );
                    ui->lbl_out_test_2->setStyleSheet("color:red");
                }else{
                    ui->lbl_out_test_2->setText( "PASS" );
                    ui->lbl_out_test_2->setStyleSheet("color:green");

                }

            }
            if(params.tests[2] != end){
                streamObj << results<T>.test_3.first;
                ui->lbl_stat_test_3->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                streamObj << results<T>.test_3.second;
                ui->lbl_cv_test_3->setText(QString::fromStdString(streamObj.str()));
                streamObj.str("");

                if (results<T>.test_3.first > results<T>.test_3.second){
                    ui->lbl_out_test_3->setText( "FAIL" );
                    ui->lbl_out_test_3->setStyleSheet("color:red");
                }else{
                    ui->lbl_out_test_3->setText( "PASS" );
                    ui->lbl_out_test_3->setStyleSheet("color:green");

                }

            }

            }
            break;


    }

    streamObj << results<T>.gof.first;
    ui->lbl_stat_gof->setText(QString::fromStdString(streamObj.str()));
    streamObj.str("");

    streamObj << results<T>.gof.second;
    ui->lbl_cv_gof->setText(QString::fromStdString(streamObj.str()));
    streamObj.str("");

    if (results<T>.gof.first > results<T>.gof.second){
        ui->lbl_out_gof->setText( "FAIL" );
        ui->lbl_out_gof->setStyleSheet("color:red");
    }else{
        ui->lbl_out_gof->setText( "PASS" );
        ui->lbl_out_gof->setStyleSheet("color:green");
    }
    std::string dist =  (results<T>.type_dist == chronovise::distribution_t::EVT_GEV) ? "GEV": "GPD";
    ui->lbl_res_dist->setText(QString::fromStdString(dist));

    streamObj << results<T>.dist->get_location();
    ui->lbl_res_location->setText(QString::fromStdString(streamObj.str()));
    streamObj.str("");
    streamObj << results<T>.dist->get_scale();
    ui->lbl_res_scale->setText(QString::fromStdString(streamObj.str()));
    streamObj.str("");
    streamObj << results<T>.dist->get_shape();
    ui->lbl_res_shape->setText(QString::fromStdString(streamObj.str()));
    streamObj.str("");

    ui->lbl_res_pwcet_103->setText(QString::fromStdString(std::to_string(results<T>.pwcet->get_wcet(1-1e-3))));
    ui->lbl_res_pwcet_109->setText(QString::fromStdString(std::to_string(results<T>.pwcet->get_wcet(1-1e-9))));


}

