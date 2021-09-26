#include "evtestimatormodel.h"


EVTEstimatorModel::EVTEstimatorModel()
{
    this->combo_box_index=0;
    this->estimator=NULL;

}


void EVTEstimatorModel::set_combo_box_index(int index)
{
    this->combo_box_index=index;
}

void EVTEstimatorModel::set_estimator(int type)
{
    switch(type)
    {
        case 1:             //PWM
        {
            this->estimator=std::make_unique<Estimator_PWM<unsigned int, double>>();
        } break;

        case 2:             //MLE
        {
            this->estimator=std::make_unique<Estimator_MLE<unsigned int, double>>();
        }break;

        case 3:             //GMLE
        {
            this->estimator=std::make_unique<Estimator_MLE<unsigned int, double, true>>();
        }break;

        default:
            ;
    }

}


int EVTEstimatorModel::get_combo_box_index()
{
    return this->combo_box_index;
}

std::unique_ptr<Estimator<unsigned int, double>> EVTEstimatorModel::get_estimator()
{
    return std::move(this->estimator);
}

