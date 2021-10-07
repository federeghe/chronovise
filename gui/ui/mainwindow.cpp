#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "chronovise_helper.h"
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

