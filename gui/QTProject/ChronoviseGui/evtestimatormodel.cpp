#include "evtestimatormodel.h"

EVTEstimatorModel::EVTEstimatorModel()
{
    this->combo_box_index=0;
}


void EVTEstimatorModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}
void EVTEstimatorModel::set_pwm_estimator()
{
    this->pwm_estimator=new Estimator_PWM<unsigned int, double>();
}
void EVTEstimatorModel::set_mle_estimator()
{
    this->mle_estimator=new Estimator_MLE<unsigned int, double>();
}
void EVTEstimatorModel::set_gmle_estimator()
{
    this->gmle_estimator=new Estimator_MLE<unsigned int, double, true>();
}


int EVTEstimatorModel::get_combo_box_index()
{
    return this->combo_box_index;
}

Estimator_PWM<unsigned int, double>* EVTEstimatorModel::get_pwm_estimator()
{
    return this->pwm_estimator;
}
Estimator_MLE<unsigned int, double> *EVTEstimatorModel::get_mle_estimator()
{
    return this->mle_estimator;
}
Estimator_MLE<unsigned int, double, true>* EVTEstimatorModel::get_gmle_estimator()
{
    return this->gmle_estimator;
}

EVTEstimatorModel::~EVTEstimatorModel()
{
    delete this->pwm_estimator;
    delete this->mle_estimator;
    delete this->gmle_estimator;
}
