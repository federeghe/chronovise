#include "testpremodel.h"

TestPreModel::TestPreModel()
{
    this->combo_box_index=0;
    this->significance_level=0.0;
    this->trend_class="";
}


void TestPreModel::set_combo_box_index(int value)
{
    this->combo_box_index=value;
}

void TestPreModel::set_significance_level(double value)
{
    this->significance_level=value;
}

void TestPreModel::set_trend_class(string str)
{
    this->trend_class=str;
}

void TestPreModel::set_n_lags(unsigned int n_lags)
{
    this->n_lags=n_lags;
}

void TestPreModel::set_ljungBox_test(double significance_level, int n_lags)
{
    this->ljungBox_test=new TestLjungBox<unsigned int, double>(significance_level, n_lags);
}
void TestPreModel::set_rs_test(double significance_level)
{
    this->rs_test=new TestRS<unsigned int, double>(significance_level);
}
void TestPreModel::set_bds_test(double significance_level)
{
    this->bds_test=new TestBDS<unsigned int, double>(significance_level);
}
void TestPreModel::set_kpss_test(double significance_level, int lags, string trend)
{
   if(trend=="level")
   {
       this->kpss_test=new TestKPSS<unsigned int, double>(significance_level,lags,test_kpss_trend_t::LEVEL);
   }
   if(trend=="trend")
   {
       this->kpss_test=new TestKPSS<unsigned int, double>(significance_level,lags,test_kpss_trend_t::TREND);
   }
}

void TestPreModel::set_critical_value(double value)
{
    this->critical_value=value;
}
void TestPreModel::set_statistic(double value)
{
    this->statistic=value;
}
void TestPreModel::set_reject(bool value)
{
    this->reject=value;
}


double TestPreModel::get_significance_level()
{
    return this->significance_level;
}
int TestPreModel::get_combo_box_index()
{
    return this->combo_box_index;
}
string TestPreModel::get_trend_class()
{
    return this->trend_class;
}
unsigned int TestPreModel::get_n_lags()
{
    return this->n_lags;
}

TestLjungBox<unsigned int, double>* TestPreModel::get_ljungBox_test()
{
    return this->ljungBox_test;
}
TestRS<unsigned int, double>* TestPreModel::get_rs_test()
{
    return this->rs_test;
}
TestBDS<unsigned int, double>* TestPreModel::get_bds_test()
{
    return this->bds_test;
}
TestKPSS<unsigned int, double>* TestPreModel::get_kpss_test()
{
    return this->kpss_test;
}

double TestPreModel::get_critical_value()
{
    return this->critical_value;
}
double TestPreModel::get_statistic()
{
    return this->statistic;
}
bool TestPreModel::get_reject()
{
    return this->reject;
}

TestPreModel::~TestPreModel()
{
    delete this->ljungBox_test;
    delete this->rs_test;
    delete this->bds_test;
    delete this->kpss_test;
}



