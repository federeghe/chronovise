#include "evtapproachmodel.h"

EVTApproachModel::EVTApproachModel()
{
    this->block_size=25;
    this->combo_box_index=0;
}

void EVTApproachModel::set_block_size(size_t block_size)
{
    this->block_size=block_size;
}
void EVTApproachModel::set_threshold(double threshold)
{
    this->threshold=threshold;
}
void EVTApproachModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}
void EVTApproachModel::set_bm_approach(size_t block_size)
{
    this->bm_approach=new EVTApproach_BM<unsigned int, double>(block_size);
}
void EVTApproachModel::set_pot_approach(double threshold)
{
    this->pot_approach=new EVTApproach_PoT<unsigned int, double>(threshold);
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
EVTApproach_BM<unsigned int, double>* EVTApproachModel::get_bm_approach()
{
    return this->bm_approach;
}
EVTApproach_PoT<unsigned int, double>* EVTApproachModel::get_pot_approach()
{
    return this->pot_approach;
}

EVTApproachModel::~EVTApproachModel()
{
    delete this->bm_approach;
    delete this->pot_approach;
}
