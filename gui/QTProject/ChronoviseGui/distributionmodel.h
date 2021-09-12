#ifndef DISTRIBUTIONMODEL_H
#define DISTRIBUTIONMODEL_H

#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include <memory>
using namespace chronovise;



class DistributionModel
{
public:
    DistributionModel();
    void set_gev_distribution(std::shared_ptr<Distribution> distribution);
    void set_gpd_distribution(std::shared_ptr<Distribution> distribution);

    std::shared_ptr<GEV_Distribution> get_gev_distribution();
    std::shared_ptr<GPD_Distribution> get_gpd_distribution();


private:
    std::shared_ptr<GEV_Distribution> gev_distribution;
    std::shared_ptr<GPD_Distribution> gpd_distribution;
};

#endif // DISTRIBUTIONMODEL_H
