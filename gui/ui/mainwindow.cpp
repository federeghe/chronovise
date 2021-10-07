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

    // clean result labels
    reset_results(ui);

    // reset progress bar
    ui->pbar_compute->setValue(0);
    ui->pbar_compute->setVisible(false);

    // reset plot config
    // reset param struct
}

void MainWindow::on_pb_compute_clicked()
{

    try{
        if (input_s == nullptr){

            QMessageBox messageBox;
            messageBox.information(0, "Info", "No file uploaded!");

        }else{

            ui->pbar_compute->setVisible(true);
            ui->pbar_compute->setRange(0,100);
            ui->pbar_compute->setValue(0);


            QLineSeries* points = new QLineSeries();

            std::thread test1;
            std::thread test2;
            std::thread test3;

            std::thread pwcet;

            // check if custom test or ppi
            switch(ui->cb_iid_test->currentIndex()){

                case 0: //PPI
                        params.iid_t = PPI;
                        break;

                case 1: //Custom Test
                        params.iid_t = Custom;

                        params.tests[0] = static_cast<t_custom_test>(ui->cb_custom_test_1->currentIndex());
                        params.tests[1] = static_cast<t_custom_test>(ui->cb_custom_test_2->currentIndex());
                        params.tests[2] = static_cast<t_custom_test>(ui->cb_custom_test_3->currentIndex());

                        break;
            }
            // parse EVT approach
            switch (ui->cb_EVT_approach->currentIndex()) {
                case 0: // Block-Maxima
                        params.evt_approach = BM;
                        break;
                case 1: // Peak over Threshold
                        params.evt_approach = PoT;
                        break;
                case 2: // MBPTA-CV
                        params.evt_approach = CV;
                        break;
            }
            //parse EVT estimator
            switch (ui->cb_EVT_estimator->currentIndex()) {

                case 0: //MLE
                        params.evt_estimator = MLE;
                        break;
                case 1: //PWM
                        params.evt_estimator = PWM;
                        break;
            }
            //parse GoF test
            switch (ui->cb_GoF_test->currentIndex()) {
                case 0: //kolmorov-smirnov
                        params.gof = KS;
                        break;
                case 1: //Anderson-Darling
                        params.gof = AD;
                        break;
                case 2: // Anderson-Darling modified
                        params.gof = mod_AD;
                        break;

            }

            // check if input data are integer or double
            // and prepare MeasurePool
            if(ui->rb_integer->isChecked()){

                chronovise::MeasuresPool<int,unsigned long> mp;

                fillMeasurePool<unsigned long>(mp);

                ui->pbar_compute->setValue(5);

                unsigned long max;
                unsigned long min;

                if (ui->in_x_scale_max->text()== "" && ui->in_x_scale_min->text()== ""){

                    max = mp.max()+5000;
                    min = mp.min();


                    ui->in_x_scale_max->setText(QString::fromStdString(std::to_string(max)));
                    ui->in_x_scale_min->setText(QString::fromStdString(std::to_string(min)));

                }else{

                    min = ui->in_x_scale_min->text().toULong();
                    max = ui->in_x_scale_max->text().toULong();

                }


                //execute tests

                if(params.iid_t == Custom){


                    test1 = std::thread(custom_test<unsigned long>,std::ref(mp), std::ref(params.tests[0]), 0.05, std::ref(results<unsigned long>.test_1));


                    test2 = std::thread(custom_test<unsigned long>,std::ref(mp), std::ref(params.tests[1]), 0.05, std::ref(results<unsigned long>.test_2));


                    test3 = std::thread(custom_test<unsigned long>,std::ref(mp), std::ref(params.tests[2]), 0.05, std::ref(results<unsigned long>.test_3));





                }else{
                    // exec ppi
                    test1 = std::thread(execute_iid_tests<unsigned long>, std::ref(mp), std::ref(results<unsigned long>));

                }

                // computation PWCET
                pwcet = std::thread(execute_pwcet_estimation<unsigned long>, std::ref(mp), std::ref(params) , std::ref(results<unsigned long>));
                pwcet.join();
                ui->pbar_compute->setValue(50);

                if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                        generate_pdf<unsigned long>(*points,min,max,results<unsigned long>);
                }else{

                    if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                        generate_cdf<unsigned long>(*points,min,max,results<unsigned long>);

                    }else{

                        generate_ccdf<unsigned long>(*points,min,max,results<unsigned long>);
                    }

                }
                ui->pbar_compute->setValue(60);

                if (test1.joinable())
                    test1.join();
                 ui->pbar_compute->setValue(70);

                if (test2.joinable())
                    test2.join();
                 ui->pbar_compute->setValue(80);
                if (test3.joinable())
                    test3.join();
                 ui->pbar_compute->setValue(90);

                if (results<unsigned long>.type_dist == chronovise::distribution_t::EVT_GEV)
                    print_results<chronovise::GEV_Distribution,unsigned long>(ui);
                else
                    print_results<chronovise::GPD_Distribution,unsigned long>(ui);



            }else{

                chronovise::MeasuresPool<int,double> mp;
                fillMeasurePool<double>(mp);

                double max;
                double min;

                if (ui->in_x_scale_max->text()== "" && ui->in_x_scale_min->text()== ""){

                    // set local to be sure that
                    // double to string conversion
                    // doesn't contain comma
                    const char* locale = "C";
                    std::locale::global(std::locale(locale));

                    max = mp.max()+5000;
                    min = mp.min();


                    ui->in_x_scale_max->setText(QString::fromStdString(std::to_string(max)));
                    ui->in_x_scale_min->setText(QString::fromStdString(std::to_string(min)));
                }else{
                    min = ui->in_x_scale_min->text().toDouble();
                    max = ui->in_x_scale_max->text().toDouble();
                }

                //execute tests

                if(params.iid_t == Custom){


                    test1 = std::thread(custom_test<double>,std::ref(mp), std::ref(params.tests[0]), 0.05, std::ref(results<double>.test_1));

                    test2 = std::thread(custom_test<double>,std::ref(mp), std::ref(params.tests[1]), 0.05, std::ref(results<double>.test_2));


                    test3 = std::thread(custom_test<double>,std::ref(mp), std::ref(params.tests[2]), 0.05, std::ref(results<double>.test_3));


                }else{
                    // exec ppi
                    test1 = std::thread(execute_iid_tests<double>,std::ref(mp), std::ref(results<double>));
                    ui->pbar_compute->setValue(50);
                }

                // computation PWCET
                pwcet = std::thread(execute_pwcet_estimation<double>,std::ref(mp), std::ref(params) ,std::ref(results<double>));

                execute_pwcet_estimation<double>(mp, params,results<double>);

                // needs to wait since we have to generate distribution points
                pwcet.join();


                if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                        generate_pdf<double>(*points,min,max,results<double>);
                }else{

                    if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                        generate_cdf<double>(*points,min,max,results<double>);

                    }else{

                        generate_ccdf<double>(*points,min,max,results<double>);
                    }

                }
                if (results<double>.type_dist == chronovise::distribution_t::EVT_GEV)
                    print_results<chronovise::GEV_Distribution,double>(ui);
                else
                    print_results<chronovise::GPD_Distribution,double>(ui);
                ui->pbar_compute->setValue(60);

                if (test1.joinable())
                    test1.join();
                 ui->pbar_compute->setValue(70);

                if (test2.joinable())
                    test2.join();
                 ui->pbar_compute->setValue(80);
                if (test3.joinable())
                    test3.join();
                 ui->pbar_compute->setValue(90);

            }

            if(ui->bg_yaxis_plot->checkedButton()->text().operator==("Linear"))
                print_plot(*points,false);
            else
                print_plot(*points,true);


            ui->pbar_compute->setValue(100);
    }


    }catch(std::exception &e){
        QMessageBox messageBox;
        messageBox.critical(0, "Error", e.what());
    }

}


void MainWindow::on_bg_funct_plot_buttonClicked(QAbstractButton *button){



    // check if chart is displayed
    if( ui->chart_view->chart()->series().size() > 0 ){

        ui->chart_view->chart()->removeAllSeries();


        QLineSeries* points = new QLineSeries();

        if(ui->rb_integer->isChecked()){

            unsigned long min = ui->in_x_scale_min->text().toLong();
            unsigned long max = ui->in_x_scale_max->text().toLong();


            if(button->text() == "PDF"){

                    generate_pdf<unsigned long>(*points,min,max,results<unsigned long>);
            }else{

                if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                    generate_cdf<unsigned long>(*points,min,max,results<unsigned long>);

                }else{

                    generate_ccdf<unsigned long>(*points,min,max,results<unsigned long>);
                }


            }
        }else{

            double min = ui->in_x_scale_min->text().toDouble();
            double max = ui->in_x_scale_max->text().toDouble();


            if(button->text() == "PDF"){

                    generate_pdf<double>(*points,min,max,results<double>);
            }else{

                if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                    generate_cdf<double>(*points,min,max,results<double>);

                }else{

                    generate_ccdf<double>(*points,min,max,results<double>);
                }

            }


        }
        if(ui->bg_yaxis_plot->checkedButton()->text().operator==("Linear"))
            print_plot(*points,false);
        else
            print_plot(*points,true);

    }

}

void MainWindow::on_bg_yaxis_plot_buttonClicked(QAbstractButton *button){


    QChart *chart = ui->chart_view->chart();

    // check if chart is displayed
    if( chart->series().size() > 0 ){
        if (button->text() == "Logarithmic"){


            QAbstractAxis *old_axis = chart->axes(Qt::Vertical).constFirst();
            chart->removeAxis(old_axis);
            QLogValueAxis *axisY = new QLogValueAxis();
            axisY->setBase(10);
            axisY->setLabelFormat("%g");
            axisY->setMinorTickCount(-1);
            axisY->setTitleText("p");

            chart->addAxis(axisY,Qt::AlignLeft);
            chart->series().constFirst()->attachAxis(axisY);
            ui->chart_view->setRenderHint(QPainter::Antialiasing);
        }
        if (button->text() == "Linear"){

            QAbstractAxis *old_axis = chart->axes(Qt::Vertical).constFirst();
            chart->removeAxis(old_axis);
            QValueAxis *axisY = new QValueAxis();
            axisY->setTitleText("p");

            chart->addAxis(axisY,Qt::AlignLeft);
            chart->series().constFirst()->attachAxis(axisY);
            ui->chart_view->setRenderHint(QPainter::Antialiasing);
        }


    }

}



void MainWindow::print_plot(QLineSeries &points, bool log_scale){


    QChart *chart = ui->chart_view->chart();
    chart->removeAllSeries();
    chart->removeAxis(chart->axes().constFirst());
    chart->removeAxis(chart->axes().constFirst());
    chart->createDefaultAxes();
    chart->legend()->hide();


    QAbstractAxis *axisY;

    QValueAxis *axisX = new QValueAxis();
    axisX->setTitleText("WCET");
    chart->addAxis(axisX, Qt::AlignBottom);


    if (log_scale){


        axisY = new QLogValueAxis();
        ((QLogValueAxis)axisY).setBase(10);
        ((QLogValueAxis)axisY).setLabelFormat("%g");
        ((QLogValueAxis)axisY).setMinorTickCount(-1);


    }else{
        axisY = new  QValueAxis();
    }


    axisY->setTitleText("p");
    chart->addAxis(axisY, Qt::AlignLeft);

    chart->addSeries(&points);

    points.attachAxis(axisX);
    points.attachAxis(axisY);

    ui->chart_view->setChart(chart);

    ui->chart_view->setRenderHint(QPainter::Antialiasing);


}



/*
 * Event: currentIndexChanged on iid_test combobox
 * Fills the tests combo when "Custom Test" is chosen
*/

void MainWindow::on_cb_iid_test_currentIndexChanged(int index)
{
    // check if custom test is selected
    if (index == 1){
        // check if custom test box are filled
        if (ui->cb_custom_test_1->count() == 0 &&
               ui->cb_custom_test_2->count() == 0 &&
               ui->cb_custom_test_3->count() == 0){


            //iterate over t_custom_test
            for (int i =0;  i < end; i++ ){

                ui->cb_custom_test_1->addItem(custom_test_str[i]);
                ui->cb_custom_test_2->addItem(custom_test_str[i]);
                ui->cb_custom_test_3->addItem(custom_test_str[i]);
            }
            ui->cb_custom_test_1->addItem(" ");
            ui->cb_custom_test_2->addItem(" ");
            ui->cb_custom_test_3->addItem(" ");


        }

    }
}


void MainWindow::on_in_x_scale_min_editingFinished()
{
    double min = ui->in_x_scale_min->text().toDouble();
    double max = ui->in_x_scale_max->text().toDouble();
    QLineSeries *points = new QLineSeries();

    if(ui->rb_integer->isChecked()){
        if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                generate_pdf<unsigned long>(*points,min,max,results<unsigned long>);
        }else{

            if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                generate_cdf<unsigned long>(*points,min,max,results<unsigned long>);

            }else{

                generate_ccdf<unsigned long>(*points,min,max,results<unsigned long>);
            }

        }

    }else{
        if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                generate_pdf<double>(*points,min,max,results<double>);
        }else{

            if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                generate_cdf<double>(*points,min,max,results<double>);

            }else{

                generate_ccdf<double>(*points,min,max,results<double>);
            }

        }
    }


    if(ui->bg_yaxis_plot->checkedButton()->text().operator==("Linear"))
        print_plot(*points,false);
    else
        print_plot(*points,true);

}

void MainWindow::on_in_x_scale_max_editingFinished()
{
    double min = ui->in_x_scale_min->text().toDouble();
    double max = ui->in_x_scale_max->text().toDouble();
    QLineSeries *points = new QLineSeries();

    if(ui->rb_integer->isChecked()){
        if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                generate_pdf<unsigned long>(*points,min,max,results<unsigned long>);
        }else{

            if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                generate_cdf<unsigned long>(*points,min,max,results<unsigned long>);

            }else{

                generate_ccdf<unsigned long>(*points,min,max,results<unsigned long>);
            }

        }

    }else{
        if(ui->bg_funct_plot->checkedButton()->text() == "PDF"){

                generate_pdf<double>(*points,min,max,results<double>);
        }else{

            if(ui->bg_funct_plot->checkedButton()->text() == "CDF"){

                generate_cdf<double>(*points,min,max,results<double>);

            }else{

                generate_ccdf<double>(*points,min,max,results<double>);
            }

        }
    }


    if(ui->bg_yaxis_plot->checkedButton()->text().operator==("Linear"))
        print_plot(*points,false);
    else
        print_plot(*points,true);

}


void MainWindow::on_pc_about_clicked()
{


    QMessageBox about;

    about.setText("<h1>chronovise</h1>");
    about.setInformativeText("<a href='https://github.com/federeghe/chronovise'>Source Code</a><br><ul>Authors:<li> Federico Reghenzani,</li><li> Giuseppe Massari,</li><li> Stefano Irno Consalvo</li></ul>");
    about.setStandardButtons(QMessageBox::Ok);
    QPixmap img;

    img.load("../ui/res/logo.svg");
    img = img.scaled(70,70);
    about.setIconPixmap(img);
    about.setDefaultButton(QMessageBox::Ok);
    about.show();
    about.exec();

}


void MainWindow::on_pb_save_plot_clicked()
{

    QPixmap p = ui->chart_view->grab();
    QOpenGLWidget *glWidget  = ui->chart_view->findChild<QOpenGLWidget*>();
    if(glWidget){
        QPainter painter(&p);
        QPoint d = glWidget->mapToGlobal(QPoint()) - ui->chart_view->mapToGlobal(QPoint());
        painter.setCompositionMode(QPainter::CompositionMode_SourceAtop);
        painter.drawImage(d, glWidget->grabFramebuffer());
        painter.end();
    }

    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save Plot"), "",
        tr("PNG (*.png);;"));
    p.save(fileName+".png", "PNG");
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



template<typename T>
void generate_pdf(QLineSeries &points, double min, double max, t_computation_results<T> &results){

    double y;
    QPointF p;
    for (double i = min; i < max; i+=1) {
        y = results.dist->pdf(i);

        if (y > 0){ // avoid 0 and negative points for log view
            p = QPointF(i,y);
            points.append(p);
        }
    }



}

template<typename T>
void generate_cdf(QLineSeries &points, double min, double max, t_computation_results<T> &results){


    QPointF p;
    double y;
    for (double i = min; i < max; i+=1) {

        y = results.dist->cdf(i);

        if (y > 0){ // avoid 0 and negative points for log view
            p = QPointF(i,y);
            points.append(p);
        }
    }



}
template<typename T>
void generate_ccdf(QLineSeries &points, double min, double max, t_computation_results<T> &results){

    double y;
    QPointF p;
    for (double i = min; i < max; i+=1) {
        y = 1 - results.dist->cdf(i);

        if (y > 0){ // avoid 0 and negative points for log view
            p = QPointF(i,y);
            points.append(p);
        }
    }



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


