#include "testpostmodel.h"

TestPostModel::TestPostModel()
{
    this->combo_box_index=0;
    this->significance_level=0.0;
    this->test=NULL;
}

void TestPostModel::set_significance_level(double value)
{
    this->significance_level=value;
}

void TestPostModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}

void TestPostModel::set_test(int type,int distribution_type)
{
    switch(type)
    {
        case 1:
        {
            if(distribution_type==1)
                this->test=make_shared<TestKS<unsigned int, double>>(this->significance_level,distribution_t::EVT_GEV);
            if(distribution_type==2)
                this->test=make_shared<TestKS<unsigned int, double>>(this->significance_level,distribution_t::EVT_GPD);
        }break;
        case 2:
        {
            if(distribution_type==1)
                this->test=make_shared<TestCvM<unsigned int, double>>(this->significance_level,distribution_t::EVT_GEV);
            if(distribution_type==2)
                this->test=make_shared<TestCvM<unsigned int, double>>(this->significance_level,distribution_t::EVT_GPD);
        }break;
        case 3:
        {
            if(distribution_type==1)
                this->test=make_shared<TestAD<unsigned int, double>>(this->significance_level,distribution_t::EVT_GEV, false, 0);
            if(distribution_type==2)
                this->test=make_shared<TestAD<unsigned int, double>>(this->significance_level,distribution_t::EVT_GPD, false, 0);
        }break;
        case 4:
        {
            if(distribution_type==1)
                this->test=make_shared<TestAD<unsigned int, double>>(this->significance_level,distribution_t::EVT_GEV, true, 0);
            if(distribution_type==2)
                this->test=make_shared<TestAD<unsigned int, double>>(this->significance_level,distribution_t::EVT_GPD, true, 0);
        }break;

        default:
            ;
    }
}



void TestPostModel::set_reject(bool value)
{
    this->reject=value;
}
void TestPostModel::set_critical_value(double value)
{
    this->critical_value=value;
}
void TestPostModel::set_statistic(double value)
{
    this->statistic=value;
}
double TestPostModel::get_significance_level()
{
    return this->significance_level;
}

int TestPostModel::get_combo_box_index()
{
    return this->combo_box_index;
}

shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> TestPostModel::get_test()
{
    return this->test;
}

bool TestPostModel::get_reject()
{
    return this->reject;
}
double TestPostModel::get_statistic()
{
    return this->statistic;
}
double TestPostModel::get_critical_value()
{
    return this->critical_value;
}


