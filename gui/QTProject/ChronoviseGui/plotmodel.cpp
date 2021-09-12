#include "plotmodel.h"

PlotModel::PlotModel()
{

}

QVector<double> PlotModel::get_xpdf()
{
    return this->xpdf;
}
QVector<double> PlotModel::get_ypdf()
{
    return this->ypdf;
}

QVector<double> PlotModel::get_xcdf()
{
    return this->xcdf;
}
QVector<double> PlotModel::get_ycdf()
{
    return this->ycdf;
}

QVector<double> PlotModel::get_xccdf()
{
    return this->xccdf;
}
QVector<double> PlotModel::get_yccdf()
{
    return this->yccdf;
}





void PlotModel::add_point_pdf(double x,double y)
{
    this->xpdf.append(x);
    this->ypdf.append(y);
}

void PlotModel::add_point_cdf(double x,double y)
{
    this->xcdf.append(x);
    this->ycdf.append(y);
}

void PlotModel::add_point_ccdf(double x,double y)
{
    this->xccdf.append(x);
    this->yccdf.append(y);
}


void PlotModel::clear_plot_pdf()
{
    this->xpdf.clear();
    this->ypdf.clear();
}
void PlotModel::clear_plot_cdf()
{
    this->xcdf.clear();
    this->ycdf.clear();
}
void PlotModel::clear_plot_ccdf()
{
    this->xccdf.clear();
    this->yccdf.clear();
}
