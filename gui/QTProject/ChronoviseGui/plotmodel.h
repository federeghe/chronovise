#ifndef PLOTMODEL_H
#define PLOTMODEL_H

#include<QVector>

class PlotModel
{
public:
    PlotModel();
    ~PlotModel()=default;
    void add_point_pdf(double x,double y);
    void add_point_cdf(double x,double y);
    void add_point_ccdf(double x,double y);

    void clear_plot_pdf();
    void clear_plot_cdf();
    void clear_plot_ccdf();

    QVector<double> get_xpdf();
    QVector<double> get_ypdf();

    QVector<double> get_xcdf();
    QVector<double> get_ycdf();

    QVector<double> get_xccdf();
    QVector<double> get_yccdf();



private:
    QVector<double> xpdf,ypdf;
    QVector<double> xcdf,ycdf;
    QVector<double> xccdf,yccdf;


};

#endif // PLOTMODEL_H
