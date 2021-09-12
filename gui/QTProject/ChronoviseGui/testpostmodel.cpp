#include "testpostmodel.h"

TestPostModel::TestPostModel()
{
    this->combo_box_index=0;
    this->significance_level=0.0;
}

void TestPostModel::set_significance_level(double value)
{
    this->significance_level=value;
}

void TestPostModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}

void TestPostModel::set_ks_test(double significance_level,int distribution_type)
{
    if(distribution_type==1)
    {
        this->ks_test=new TestKS<unsigned int, double>(significance_level,distribution_t::EVT_GEV);
    }
    if(distribution_type==2)
    {
        this->ks_test=new TestKS<unsigned int, double>(significance_level,distribution_t::EVT_GPD);
    }
}

void TestPostModel::set_ad_test(double significance_level, int distribution_type, bool mad)
{
    if(distribution_type==1)
    {
        this->ad_test=new TestAD<unsigned int, double>(significance_level, distribution_t::EVT_GEV, mad,0);
    }
    if(distribution_type==2)
    {
        this->ad_test=new TestAD<unsigned int, double>(significance_level, distribution_t::EVT_GPD, mad, 0);
    }
}

void TestPostModel::set_cvm_test(double significance_level,int distribution_type)
{
    if(distribution_type==1)
    {
        this->cvm_test=new TestCvM<unsigned int, double>(significance_level,distribution_t::EVT_GEV);
    }
    if(distribution_type==2)
    {
        this->cvm_test=new TestCvM<unsigned int, double>(significance_level,distribution_t::EVT_GPD);
    }
}

void TestPostModel::set_reject(bool value)
{
    this->reject=value;
}


double TestPostModel::get_significance_level()
{
    return this->significance_level;
}

int TestPostModel::get_combo_box_index()
{
    return this->combo_box_index;
}

TestKS<unsigned int, double>* TestPostModel::get_ks_test()
{
    return this->ks_test;
}

TestAD<unsigned int, double>* TestPostModel::get_ad_test()
{
    return this->ad_test;
}

TestCvM<unsigned int, double>* TestPostModel::get_cvm_test()
{
    return this->cvm_test;
}

bool TestPostModel::get_reject()
{
    return this->reject;
}


TestPostModel::~TestPostModel()
{
    delete this->ks_test;
    delete this->ad_test;
    delete this->cvm_test;
}
