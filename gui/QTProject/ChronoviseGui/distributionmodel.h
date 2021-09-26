#ifndef DISTRIBUTIONMODEL_H
#define DISTRIBUTIONMODEL_H

#include "evt/gev_distribution.hpp"
#include "evt/gpd_distribution.hpp"
#include <memory>
#include <list>
using namespace chronovise;



class DistributionModel
{
public:
    DistributionModel();
    ~DistributionModel()=default;

   void set_dist(int evt_approach_type, std::list<std::shared_ptr<Distribution>> list);

    std::shared_ptr<GEV_Distribution> get_gev_distribution();
    std::shared_ptr<GPD_Distribution> get_gpd_distribution();


private:
    std::shared_ptr<GEV_Distribution> gev_distribution;
    std::shared_ptr<GPD_Distribution> gpd_distribution;
};

#endif // DISTRIBUTIONMODEL_H
