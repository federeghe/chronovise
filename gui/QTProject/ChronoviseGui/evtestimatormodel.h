#ifndef EVTESTIMATORMODEL_H
#define EVTESTIMATORMODEL_H

#include <memory>
#include "statistical/estimator_pwm.hpp"
#include "statistical/estimator_mle.hpp"
using namespace chronovise;

class EVTEstimatorModel
{
public:
    EVTEstimatorModel();
    ~EVTEstimatorModel()=default;
    void set_combo_box_index(int index);
    void set_estimator(int type);

    int get_combo_box_index();
    std::unique_ptr<Estimator<unsigned int, double>> get_estimator();


private:
    int combo_box_index;
    std::unique_ptr<Estimator<unsigned int, double>> estimator;

};

#endif // EVTESTIMATORMODEL_H
