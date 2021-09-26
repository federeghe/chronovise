#include "testpremodel.h"

TestPreModel::TestPreModel()
{
    this->combo_box_index=0;
    this->significance_level=0.0;
    this->trend_class="";
    this->n_lags=10;

    this->test=NULL;
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

void TestPreModel::set_test(int type)
{
    switch(type)
    {
        case 1:
        {
            if(this->trend_class=="level")
                this->test=make_shared<TestKPSS<unsigned int, double>>(this->significance_level,this->n_lags,test_kpss_trend_t::LEVEL);
            if(this->trend_class=="trend")
                this->test=make_shared<TestKPSS<unsigned int, double>>(significance_level,this->n_lags,test_kpss_trend_t::TREND);
        }break;
        case 2:
        {
            this->test=make_shared<TestBDS<unsigned int, double>>(this->significance_level);
        }break;
        case 3:
        {
            this->test=make_shared<TestLjungBox<unsigned int, double>>(this->significance_level, this->n_lags);
        }break;
        case 4:
        {
            this->test=make_shared<TestRS<unsigned int, double>>(this->significance_level);
        }break;

        default:
            ;
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

shared_ptr<StatisticalTest<unsigned int, double>> TestPreModel::get_test()
{
    return this->test;
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



