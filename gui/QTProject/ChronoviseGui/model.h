#ifndef MODEL_H
#define MODEL_H

using namespace std;

#include <sec.hpp>
#include <testpremodel.h>
#include <testpostmodel.h>
#include <fileimportmodel.h>
#include <evtapproachmodel.h>
#include <evtestimatormodel.h>
#include <distributionmodel.h>
#include "plotmodel.h"
#include <string>

using namespace chronovise;




class Model : public chronovise::SimpleExecutionContext<unsigned int, double>
{

public:
    Model() noexcept;

    virtual ~Model();
    virtual exit_code_t onSetup() noexcept override;
    virtual exit_code_t onConfigure() noexcept override;
    virtual exit_code_t onRun() noexcept override;
    virtual exit_code_t onMonitor() noexcept override;
    virtual exit_code_t onRelease() noexcept override;




    void set_pwcet99999(double value);
    void set_pwcet_109(double value);


    FileImportModel* get_input_file();

    TestPreModel* get_first_pre_test();
    TestPreModel* get_second_pre_test();
    TestPreModel* get_third_pre_test();

    TestPostModel* get_post_test();

    EVTApproachModel* get_evt_approach();
    EVTEstimatorModel* get_evt_estimator();
    DistributionModel* get_distribution();



    PlotModel* get_plot_data();


    double get_pwcet99999();
    double get_pwcet_109();


    void custom_run();

    void copy(Model* m);


private:

    FileImportModel* input_file;

    TestPreModel* first_pre_test;
    TestPreModel* second_pre_test;
    TestPreModel* third_pre_test;

    TestPostModel* post_test;

    EVTApproachModel* evt_approach;
    EVTEstimatorModel* evt_estimator;
    DistributionModel* distribution;

    PlotModel* plot_data;

    double pwcet99999;
    double pwcet_109;




};
#endif // MODEL_H
