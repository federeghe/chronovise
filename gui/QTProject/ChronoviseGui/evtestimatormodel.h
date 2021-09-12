#ifndef EVTESTIMATORMODEL_H
#define EVTESTIMATORMODEL_H


#include "statistical/estimator_pwm.hpp"
#include "statistical/estimator_mle.hpp"
using namespace chronovise;

class EVTEstimatorModel
{
public:
    EVTEstimatorModel();
    ~EVTEstimatorModel();
    void set_combo_box_index(int index);
    void set_pwm_estimator();
    void set_mle_estimator();
    void set_gmle_estimator();

    int get_combo_box_index();
    Estimator_PWM<unsigned int, double>* get_pwm_estimator();
    Estimator_MLE<unsigned int, double>* get_mle_estimator();
    Estimator_MLE<unsigned int, double, true>* get_gmle_estimator();




private:
    int combo_box_index;
    Estimator_PWM<unsigned int, double>* pwm_estimator;
    Estimator_MLE<unsigned int, double>* mle_estimator;
    Estimator_MLE<unsigned int, double,true>* gmle_estimator;

};

#endif // EVTESTIMATORMODEL_H
