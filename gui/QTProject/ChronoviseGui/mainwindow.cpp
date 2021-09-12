#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QFileDialog>
#include <QInputDialog>
#include <QMessageBox>
#include <QDir>
#include <model.h>
#include <QLayout>
#include <math.h>


MainWindow::MainWindow(QWidget *parent, Model* model)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->model = model;
    this->setup_plot();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete this->model;

}


//initialize graph and the event signal couples
void MainWindow::setup_plot()
{
    this->ui->pdf->addGraph();
    this->ui->cdf->addGraph();
    this->ui->ccdf->addGraph();
    //connecting event when x axis changes its range to "adding new point to the plot" function
    QObject::connect(this->ui->pdf->xAxis,SIGNAL (rangeChanged(const QCPRange)),this,SLOT (extend_plot_pdf(const QCPRange)));
    QObject::connect(this->ui->cdf->xAxis,SIGNAL (rangeChanged(const QCPRange)),this,SLOT (extend_plot_cdf(const QCPRange)));
    QObject::connect(this->ui->ccdf->xAxis,SIGNAL (rangeChanged(const QCPRange)),this,SLOT (extend_plot_ccdf(const QCPRange)));
}

//these 3 initialize plot functions
void MainWindow::initialize_plot_pdf(std::shared_ptr<Distribution> distribution)
{

    this->ui->pdf->setInteraction(QCP::iRangeDrag, true);
    this->ui->pdf->setInteraction(QCP::iRangeZoom, true);
    for(double i=0.0;i<=100.0;i+=0.25)
    {
        //this->model->get_plot_data()->add_point_pdf(i,exp((i)));
        this->model->get_plot_data()->add_point_pdf(i,distribution->pdf(i));
    }
    this->ui->pdf->graph(0)->setData(this->model->get_plot_data()->get_xpdf(),this->model->get_plot_data()->get_ypdf());
    this->ui->pdf->rescaleAxes();
    //this->ui->pdf->xAxis->setRange(-1.0,100.0);
    this->ui->pdf->replot();
    this->ui->pdf->update();
}
void MainWindow::initialize_plot_cdf(std::shared_ptr<Distribution> distribution)
{

    this->ui->cdf->setInteraction(QCP::iRangeDrag, true);
    this->ui->cdf->setInteraction(QCP::iRangeZoom, true);
    for(double i=0.0;i<=100.0;i+=0.25)
    {
        //this->model->get_plot_data()->add_point_cdf(i,exp((i)));
        this->model->get_plot_data()->add_point_cdf(i,distribution->cdf(i));
    }
    this->ui->cdf->graph(0)->setData(this->model->get_plot_data()->get_xcdf(),this->model->get_plot_data()->get_ycdf());
    this->ui->cdf->rescaleAxes();
    //this->ui->cdf->xAxis->setRange(-1.0,100.0);
    this->ui->cdf->replot();
    this->ui->cdf->update();
}
void MainWindow::initialize_plot_ccdf(std::shared_ptr<Distribution> distribution)
{

    this->ui->ccdf->setInteraction(QCP::iRangeDrag, true);
    this->ui->ccdf->setInteraction(QCP::iRangeZoom, true);
    for(double i=0;i<=100.0;i+=0.25)
    {
        //this->model->get_plot_data()->add_point_ccdf(i,exp((i)));
        this->model->get_plot_data()->add_point_ccdf(i,1-distribution->cdf(i));
    }
    this->ui->ccdf->graph(0)->setData(this->model->get_plot_data()->get_xccdf(),this->model->get_plot_data()->get_yccdf());
    this->ui->ccdf->rescaleAxes();
    //this->ui->ccdf->xAxis->setRange(-1.0,100.0);
    this->ui->ccdf->replot();
    this->ui->ccdf->update();
}


//function to call when user change the range of view of the plot
void MainWindow::extend_plot_pdf(const QCPRange &newRange)
{
    if(this->model->get_evt_approach()->get_combo_box_index()==1)
    {
        //this->model->get_plot_data()->add_point_pdf(newRange.upper, exp(newRange.upper));
        this->model->get_plot_data()->add_point_pdf(newRange.upper, this->model->get_distribution()->get_gev_distribution()->pdf(newRange.upper));
    }
    if(this->model->get_evt_approach()->get_combo_box_index()==2)
    {
        //this->model->get_plot_data()->add_point_cdf(newRange.upper, exp(newRange.upper));

        this->model->get_plot_data()->add_point_pdf(newRange.upper, this->model->get_distribution()->get_gpd_distribution()->pdf(newRange.upper));
    }
    this->ui->pdf->graph(0)->setData(this->model->get_plot_data()->get_xpdf(),this->model->get_plot_data()->get_ypdf());
    this->ui->pdf->replot();
    this->ui->pdf->update();
}
void MainWindow::extend_plot_cdf(const QCPRange &newRange)
{
    if(this->model->get_evt_approach()->get_combo_box_index()==1)
    {
        //this->model->get_plot_data()->add_point_cdf(newRange.upper, exp(newRange.upper));
        this->model->get_plot_data()->add_point_cdf(newRange.upper, this->model->get_distribution()->get_gev_distribution()->cdf(newRange.upper));
    }
    if(this->model->get_evt_approach()->get_combo_box_index()==2)
    {
        //this->model->get_plot_data()->add_point_cdf(newRange.upper, exp(newRange.upper));
        this->model->get_plot_data()->add_point_cdf(newRange.upper, this->model->get_distribution()->get_gpd_distribution()->cdf(newRange.upper));
    }
    this->ui->cdf->graph(0)->setData(this->model->get_plot_data()->get_xcdf(),this->model->get_plot_data()->get_ycdf());
    this->ui->cdf->replot();
    this->ui->cdf->update();
}
void MainWindow::extend_plot_ccdf(const QCPRange &newRange)
{
    if(this->model->get_evt_approach()->get_combo_box_index()==1)
    {
        //this->model->get_plot_data()->add_point_ccdf(newRange.upper, exp(newRange.upper));
        this->model->get_plot_data()->add_point_ccdf(newRange.upper, 1-this->model->get_distribution()->get_gev_distribution()->cdf(newRange.upper));
    }
    if(this->model->get_evt_approach()->get_combo_box_index()==2)
    {
        //this->model->get_plot_data()->add_point_ccdf(newRange.upper, exp(newRange.upper));
        this->model->get_plot_data()->add_point_ccdf(newRange.upper, 1-this->model->get_distribution()->get_gpd_distribution()->cdf(newRange.upper));
    }
    this->ui->ccdf->graph(0)->setData(this->model->get_plot_data()->get_xccdf(),this->model->get_plot_data()->get_yccdf());
    this->ui->ccdf->replot();
    this->ui->ccdf->update();
}

//when pressing logarithm radio button
void MainWindow::on_log_rb_clicked()
{
    this->ui->pdf->yAxis->setScaleType(QCPAxis::stLogarithmic);
    //this->ui->pdf->rescaleAxes();
    this->ui->pdf->replot();
    this->ui->pdf->update();
}
void MainWindow::on_log_rb_2_clicked()
{
    this->ui->cdf->yAxis->setScaleType(QCPAxis::stLogarithmic);
    //this->ui->cdf->rescaleAxes();
    this->ui->cdf->replot();
    this->ui->cdf->update();
}
void MainWindow::on_log_rb_3_clicked()
{
    this->ui->ccdf->yAxis->setScaleType(QCPAxis::stLogarithmic);
    //this->ui->ccdf->rescaleAxes();
    this->ui->ccdf->replot();
    this->ui->ccdf->update();
}


//when pressing linear radio button
void MainWindow::on_linear_rb_clicked()
{
    this->ui->pdf->yAxis->setScaleType(QCPAxis::stLinear);
    //this->ui->pdf->xAxis->setRange(-1.0,100.0);
    //this->ui->pdf->rescaleAxes();
    this->ui->pdf->replot();
    this->ui->pdf->update();
}
void MainWindow::on_linear_rb_2_clicked()
{
    this->ui->cdf->yAxis->setScaleType(QCPAxis::stLinear);
    //this->ui->cdf->rescaleAxes();
    this->ui->cdf->replot();
    this->ui->cdf->update();
}
void MainWindow::on_linear_rb_3_clicked()
{
    this->ui->ccdf->yAxis->setScaleType(QCPAxis::stLinear);
    //this->ui->ccdf->rescaleAxes();
    this->ui->ccdf->replot();
    this->ui->ccdf->update();
}


void MainWindow::on_input_file_button_clicked()
{
    QString filter = "All File (*.*) ;; Text File (*.txt)";
    QString file_name = QFileDialog::getOpenFileName(this,"Open a file",QDir::homePath(),filter);
    QMessageBox::information(this,"",file_name);
    this->model->get_input_file()->set_input_file_name(file_name.toStdString());
}


//choice first pre-test
void MainWindow::on_test1_cb_currentIndexChanged(int index)
{
    this->model->get_first_pre_test()->set_combo_box_index(index);
    if(index!=0 && (index==this->model->get_second_pre_test()->get_combo_box_index() || index==this->model->get_third_pre_test()->get_combo_box_index()))
    {
        QMessageBox::information(this,"Warning","invalid input,test already selected");
        this->ui->test1_cb->setCurrentIndex(0);
    }
    else
    {
        if(index==1 || index==3)
            this->model->get_first_pre_test()->set_n_lags((QInputDialog::getInt(this,"Number of Lags","enter the number of lags you want to use for the test",10)));
    }

    //this->ui->statusBar->showMessage(QString::number((this->model->get_first_pre_test()->get_combo_box_index())));
    //this->ui->statusBar->showMessage(QString::number((this->model->get_first_pre_test()->get_n_lags())));
}
//choice second pre-test
void MainWindow::on_test2_cb_currentIndexChanged(int index)
{
    this->model->get_second_pre_test()->set_combo_box_index(index);
    if(index!=0 && this->model->get_first_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 1 not selected");
        this->ui->test2_cb->setCurrentIndex(0);
    }
    else
    {
        if(index!=0 && (index==this->model->get_first_pre_test()->get_combo_box_index() || index==this->model->get_third_pre_test()->get_combo_box_index()))
        {
            QMessageBox::information(this,"Warning","invalid input,test already selected");
            this->ui->test2_cb->setCurrentIndex(0);
        }
        else
        {
            if(index==1 || index==3)
                this->model->get_second_pre_test()->set_n_lags((QInputDialog::getInt(this,"Number of Lags","enter the number of lags you want to use for the test",10)));

        }
     }

    this->ui->statusBar->showMessage(QString::number((this->model->get_second_pre_test()->get_combo_box_index())));
}
//choice third pre-test
void MainWindow::on_test3_cb_currentIndexChanged(int index)
{
    this->model->get_third_pre_test()->set_combo_box_index(index);
    if(index!=0 && (this->model->get_first_pre_test()->get_combo_box_index()==0 || this->model->get_second_pre_test()->get_combo_box_index()==0))
    {
        QMessageBox::information(this,"Warning","either test 1 or 2  not selected");
        this->ui->test3_cb->setCurrentIndex(0);
    }
    else
    {
        if(index!=0 && (index==this->model->get_first_pre_test()->get_combo_box_index() || index==this->model->get_second_pre_test()->get_combo_box_index()))
        {
            QMessageBox::information(this,"Warning","invalid input,test already selected");
            this->ui->test3_cb->setCurrentIndex(0);
        }
        else
        {
            if(index==1 || index==3)
                this->model->get_third_pre_test()->set_n_lags((QInputDialog::getInt(this,"Number of Lags","enter the number of lags you want to use for the test",10)));
        }

    }

    //this->ui->statusBar->showMessage(QString::number((this->model->get_third_pre_test()->get_combo_box_index())));
}

//significance level for the test
void MainWindow::on_sig_lev_cb_1_currentIndexChanged(int index)
{
    if(index!=0 && this->model->get_first_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 1 not selected");
        this->ui->sig_lev_cb_1->setCurrentIndex(0);

    }
    if(index==0)
    {
        this->model->get_first_pre_test()->set_significance_level(0.0);
    }
    if(index==1)
    {
        if(this->model->get_first_pre_test()->get_combo_box_index()==2 || this->model->get_first_pre_test()->get_combo_box_index()==4)
        {
            QMessageBox::information(this,"Warning","only 0.05 is available for this estimator");
            this->ui->sig_lev_cb_1->setCurrentIndex(2);
        }
        else
        {
            this->model->get_first_pre_test()->set_significance_level(0.01);
        }

    }
    if(index==2)
    {
        this->model->get_first_pre_test()->set_significance_level(0.05);
    }
}

void MainWindow::on_sig_lev_cb_2_currentIndexChanged(int index)
{
    if(index!=0 && this->model->get_second_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 2 not selected");
        this->ui->sig_lev_cb_2->setCurrentIndex(0);

    }
    if(index==0)
    {
        this->model->get_second_pre_test()->set_significance_level(0.0);
    }
    if(index==1)
    {
        if(this->model->get_second_pre_test()->get_combo_box_index()==2 || this->model->get_second_pre_test()->get_combo_box_index()==4)
        {
            QMessageBox::information(this,"Warning","only 0.05 is available for this estimator");
            this->ui->sig_lev_cb_2->setCurrentIndex(2);
        }
        else
        {
            this->model->get_second_pre_test()->set_significance_level(0.01);
        }

    }
    if(index==2)
    {
        this->model->get_second_pre_test()->set_significance_level(0.05);
    }

}

void MainWindow::on_sig_lev_cb_3_currentIndexChanged(int index)
{
    if(index!=0 && this->model->get_third_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 3 not selected");
        this->ui->sig_lev_cb_3->setCurrentIndex(0);

    }
    if(index==0)
    {
        this->model->get_third_pre_test()->set_significance_level(0.0);
    }
    if(index==1)
    {
        if(this->model->get_third_pre_test()->get_combo_box_index()==2 || this->model->get_third_pre_test()->get_combo_box_index()==4)
        {
            QMessageBox::information(this,"Warning","only 0.05 is available for this estimator");
            this->ui->sig_lev_cb_3->setCurrentIndex(2);
        }
        else
        {
            this->model->get_third_pre_test()->set_significance_level(0.01);
        }

    }
    if(index==2)
    {
        this->model->get_third_pre_test()->set_significance_level(0.05);
    }
}

//trend  choice for first pretest
void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    if(index==1)
    {
        this->model->get_first_pre_test()->set_trend_class("level");
    }
    if(index==2)
    {
        this->model->get_first_pre_test()->set_trend_class("trend");
    }
    if(index==0)
    {
        this->model->get_first_pre_test()->set_trend_class("");
    }

    if(index!=0 && this->model->get_first_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 1 not selected");
        this->ui->comboBox->setCurrentIndex(0);
    }

    if(index!=0 && this->model->get_first_pre_test()->get_combo_box_index()!=1)
    {
        QMessageBox::information(this,"Warning","paramter available only for kpss test");
        this->ui->comboBox->setCurrentIndex(0);
    }

    //this->ui->statusBar->showMessage(QString::fromStdString(this->model->get_first_pre_test()->get_trend_class()));
}
//trend  choice for second pretest
void MainWindow::on_comboBox_2_currentIndexChanged(int index)
{
    if(index==1)
    {
        this->model->get_second_pre_test()->set_trend_class("level");
    }
    if(index==2)
    {
        this->model->get_second_pre_test()->set_trend_class("trend");
    }
    if(index==0)
    {
        this->model->get_second_pre_test()->set_trend_class("");
    }

    if(index!=0 && this->model->get_second_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 1 not selected");
        this->ui->comboBox_2->setCurrentIndex(0);
    }

    if(index!=0 && this->model->get_second_pre_test()->get_combo_box_index()!=1)
    {
        QMessageBox::information(this,"Warning","paramter available only for kpss test");
        this->ui->comboBox_2->setCurrentIndex(0);
    }
    //this->ui->statusBar->showMessage(QString::fromStdString(this->model->get_second_pre_test()->get_trend_class()));
}

//trend  choice for third pretest
void MainWindow::on_comboBox_3_currentIndexChanged(int index)
{
    if(index==1)
        this->model->get_third_pre_test()->set_trend_class("level");

    if(index==2)
        this->model->get_third_pre_test()->set_trend_class("trend");

    if(index==0)
        this->model->get_third_pre_test()->set_trend_class("");

    if(index!=0 && this->model->get_third_pre_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","test 1 not selected");
        this->ui->comboBox_3->setCurrentIndex(0);
    }

    if(index!=0 && this->model->get_third_pre_test()->get_combo_box_index()!=1)
    {
        QMessageBox::information(this,"Warning","paramter available only for kpss test");
        this->ui->comboBox_3->setCurrentIndex(0);
    }
    //this->ui->statusBar->showMessage(QString::fromStdString(this->model->get_third_pre_test()->get_trend_class()));

}



//choice evt approach
void MainWindow::on_evt_approach_cb_currentIndexChanged(int index)
{
    this->model->get_evt_approach()->set_combo_box_index(index);
    if(index==1)
        this->model->get_evt_approach()->set_block_size((QInputDialog::getInt(this,"Block Size","enter a value for the size of the block")));

    if(index==2)
        this->model->get_evt_approach()->set_threshold((QInputDialog::getDouble(this,"Threshold","enter a value for the threshold")));

    //this->ui->statusBar->showMessage(QString::number((this->model->get_evt_approach()->get_block_size())));
    //this->ui->statusBar->showMessage(QString::number((this->model->get_evt_approach()->get_threshold())));
    //this->ui->statusBar->showMessage(QString::number((this->model->get_evt_approach()->get_threshold())));

}

//choice evt estimator
void MainWindow::on_evt_estimator_cb_currentIndexChanged(int index)
{
    this->model->get_evt_estimator()->set_combo_box_index(index);
    if(index!=0 && this->model->get_evt_approach()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","please, choose an evt approach first");
        this->ui->evt_estimator_cb->setCurrentIndex(0);
    }
    else
    {
        if((index==2 || index==3) && this->model->get_evt_approach()->get_combo_box_index()==2)
        {
            QMessageBox::information(this,"Warning","this estimator is only available for Block-Maxima");
            this->ui->evt_estimator_cb->setCurrentIndex(0);
        }
    }
    //this->ui->statusBar->showMessage(QString::number((this->model->get_evt_estimator()->get_combo_box_index())));
}


//choice gof test
void MainWindow::on_gof_test_cb_currentIndexChanged(int index)
{
    this->model->get_post_test()->set_combo_box_index(index);
    if(index!=0 && this->model->get_evt_approach()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","evt approach not selected");
        this->ui->gof_test_cb->setCurrentIndex(0);
    }
    //this->ui->statusBar->showMessage(QString::number((this->model->get_post_test()->get_combo_box_index())));
}
//significance level for gof test
void MainWindow::on_sig_lev_cb_4_currentIndexChanged(int index)
{
    if(index!=0 && this->model->get_post_test()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","gof test not selected");
        this->ui->sig_lev_cb_4->setCurrentIndex(0);
    }
    if(index==0)
        this->model->get_post_test()->set_significance_level(0.0);

    if(index==1)
       this->model->get_post_test()->set_significance_level(0.01);

    if(index==2)
        this->model->get_post_test()->set_significance_level(0.05);

    this->ui->statusBar->showMessage(QString::number((this->model->get_post_test()->get_significance_level())));
}


//what happens when pressing compute button
void MainWindow::on_compute_button_clicked()
{
    //check if no input file is missing
    if(this->model->get_input_file()->get_input_file_name()=="")
    {
        QMessageBox::information(this,"Warning","file not selected");
        return;
    }
    //check if either evt approach or estimator is missing
    if(this->model->get_evt_approach()->get_combo_box_index()==0 || this->model->get_evt_estimator()->get_combo_box_index()==0)
    {
        QMessageBox::information(this,"Warning","either evt approach or evt estimator is missing");
        return;
    }
    //check if significance level is missing for any of the test selected either pre test or gof test
    if((this->model->get_first_pre_test()->get_significance_level()==0.0 && this->model->get_first_pre_test()->get_combo_box_index()!=0) || (this->model->get_second_pre_test()->get_significance_level()==0.0 && this->model->get_second_pre_test()->get_combo_box_index()!=0) || (this->model->get_third_pre_test()->get_significance_level()==0.0 && this->model->get_third_pre_test()->get_combo_box_index()!=0) || (this->model->get_post_test()->get_significance_level()==0.0 && this->model->get_post_test()->get_combo_box_index()!=0))
    {
       QMessageBox::information(this,"Warning","must choose a singificance level for the test");
       return;
    }
    //check if trend level is missing for kpss test
    if((this->model->get_first_pre_test()->get_trend_class()=="" && this->model->get_first_pre_test()->get_combo_box_index()==1) || (this->model->get_second_pre_test()->get_trend_class()=="" && this->model->get_second_pre_test()->get_combo_box_index()==1) || (this->model->get_third_pre_test()->get_trend_class()=="" && this->model->get_third_pre_test()->get_combo_box_index()==1))
    {
       QMessageBox::information(this,"Warning","must choose a trend option for the kpss test");
       return;
    }

    //let chronovise execute its loop
    this->model->custom_run();

    //print the result of the first pre test
    if(this->model->get_first_pre_test()->get_combo_box_index()!=0)
    {
        this->ui->test1_st_lbl->setText(QString::number(this->model->get_first_pre_test()->get_statistic()));
        this->ui->test1_c_v_lbl->setText(QString::number(this->model->get_first_pre_test()->get_critical_value()));
        if(this->model->get_first_pre_test()->get_reject()==true)
        {
            this->ui->test1_output_lbl->setStyleSheet("color: green;");
            this->ui->test1_output_lbl->setText("PASS");

        }
        else
        {
            this->ui->test1_output_lbl->setStyleSheet("color: red;");
            this->ui->test1_output_lbl->setText("FAIL");
        }

    }
    //print the result of the second pre test
    if(this->model->get_second_pre_test()->get_combo_box_index()!=0)
    {
        this->ui->test2_st_lbl->setText(QString::number(this->model->get_second_pre_test()->get_statistic()));
        this->ui->test2_c_v_lbl->setText(QString::number(this->model->get_second_pre_test()->get_critical_value()));
        if(this->model->get_second_pre_test()->get_reject()==true)
        {
            this->ui->test2_output_lbl->setStyleSheet("color: green;");
            this->ui->test2_output_lbl->setText("PASS");
        }
        else
        {
            this->ui->test2_output_lbl->setStyleSheet("color: red;");
            this->ui->test2_output_lbl->setText("FAIL");
        }

    }
    //print the result of the third pre test
    if(this->model->get_third_pre_test()->get_combo_box_index()!=0)
    {
        this->ui->test3_st_lbl->setText(QString::number(this->model->get_third_pre_test()->get_statistic()));
        this->ui->test3_c_v_lbl->setText(QString::number(this->model->get_third_pre_test()->get_critical_value()));
        if(this->model->get_third_pre_test()->get_reject()==true)
        {
            this->ui->test3_output_lbl->setStyleSheet("color: green;");
            this->ui->test3_output_lbl->setText("PASS");
        }
        else
        {
            this->ui->test3_output_lbl->setStyleSheet("color: red;");
            this->ui->test3_output_lbl->setText("FAIL");
        }
    }
    //print the result of gof test
    if(this->model->get_post_test()->get_combo_box_index()!=0)
    {
        if(this->model->get_post_test()->get_reject()==true)
        {
            this->ui->gof_ouput_lbl->setStyleSheet("color: green;");
            this->ui->gof_ouput_lbl->setText("PASS");
        }
        else
        {
            this->ui->gof_ouput_lbl->setStyleSheet("color: red;");
            this->ui->gof_ouput_lbl->setText("FAIL");
        }
    }

    //compute and print the observed wcet
    this->ui->wtime_lbl->setText(QString::number(this->model->get_input_file()->wcet_calc(this->model->get_input_file()->get_input_file_name())));
    //other results from the distribution
    this->ui->lbl_res_pwcet_103->setText(QString::number(this->model->get_pwcet99999()));
    this->ui->lbl_res_pwcet_104->setText(QString::number(this->model->get_pwcet_109()));


    //initialize the plot for the distribution
    if(this->model->get_evt_approach()->get_combo_box_index()==1)
    {
        this->initialize_plot_pdf(this->model->get_distribution()->get_gev_distribution());
        this->initialize_plot_cdf(this->model->get_distribution()->get_gev_distribution());
        this->initialize_plot_ccdf(this->model->get_distribution()->get_gev_distribution());
    }
    if(this->model->get_evt_approach()->get_combo_box_index()==2)
    {
        this->initialize_plot_pdf(this->model->get_distribution()->get_gpd_distribution());
        this->initialize_plot_cdf(this->model->get_distribution()->get_gpd_distribution());
        this->initialize_plot_ccdf(this->model->get_distribution()->get_gpd_distribution());

    }

}














