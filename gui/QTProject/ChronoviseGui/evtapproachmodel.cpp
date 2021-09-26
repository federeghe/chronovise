#include "evtapproachmodel.h"

EVTApproachModel::EVTApproachModel()
{
    this->block_size=0;
    this->combo_box_index=0;
    this->samples_test_reserve=0.1;
    this->approach=NULL;
}

void EVTApproachModel::set_block_size(size_t block_size)
{
    this->block_size=block_size;
}
void EVTApproachModel::set_threshold(double threshold)
{
    this->threshold=threshold;
}
void EVTApproachModel::set_samples_test_reserve(float reserve)
{
    this->samples_test_reserve=reserve;
}
void EVTApproachModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}
void EVTApproachModel::set_approach(int type)
{
    if(type==1)
        this->approach=make_unique<EVTApproach_BM<unsigned int, double>>(this->block_size);
    if(type==2)
        this->approach=make_unique<EVTApproach_PoT<unsigned int, double>>(this->threshold);
}


int EVTApproachModel::get_combo_box_index()
{
    return this->combo_box_index;
}
size_t EVTApproachModel::get_block_size()
{
    return this->block_size;
}
double EVTApproachModel::get_threshold()
{
    return this->threshold;
}
float EVTApproachModel::get_samples_test_reserve()
{
    return this->samples_test_reserve;
}
unique_ptr<EVTApproach<unsigned int, double>> EVTApproachModel::get_approach()
{
    return std::move(this->approach);
}

