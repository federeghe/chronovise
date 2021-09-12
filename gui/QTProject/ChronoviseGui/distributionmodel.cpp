#include "distributionmodel.h"

DistributionModel::DistributionModel()
{

}

void DistributionModel::set_gev_distribution(std::shared_ptr<Distribution> distribution)
{
    this->gev_distribution=std::dynamic_pointer_cast<GEV_Distribution>(distribution);
}
void DistributionModel::set_gpd_distribution(std::shared_ptr<Distribution> distribution)
{
    this->gpd_distribution=std::dynamic_pointer_cast<GPD_Distribution>(distribution);
}


std::shared_ptr<GEV_Distribution> DistributionModel::get_gev_distribution()
{
    return this->gev_distribution;
}
std::shared_ptr<GPD_Distribution> DistributionModel::get_gpd_distribution()
{
    return this->gpd_distribution;
}
