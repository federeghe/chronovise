#include "distributionmodel.h"



DistributionModel::DistributionModel()
{
    this->gev_distribution=NULL;
    this->gpd_distribution=NULL;
}



void DistributionModel::set_dist(int evt_approach_type, std::list<std::shared_ptr<Distribution>> list)
{
    if(evt_approach_type==1)
        this->gev_distribution=std::dynamic_pointer_cast<GEV_Distribution>(list.front());
    if(evt_approach_type==2)
        this->gpd_distribution=std::dynamic_pointer_cast<GPD_Distribution>(list.front());
}



std::shared_ptr<GEV_Distribution> DistributionModel::get_gev_distribution()
{
    return this->gev_distribution;
}
std::shared_ptr<GPD_Distribution> DistributionModel::get_gpd_distribution()
{
    return this->gpd_distribution;
}






