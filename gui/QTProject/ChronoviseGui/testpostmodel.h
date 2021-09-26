#ifndef TESTPOSTMODEL_H
#define TESTPOSTMODEL_H


using namespace std;
#include <string>

#include "statistical/test_cvm.hpp"
#include "statistical/test_ks.hpp"
#include "statistical/test_ad.hpp"
using namespace chronovise;



class TestPostModel
{
public:
    TestPostModel();
    ~TestPostModel()=default;
    void set_significance_level(double value);
    void set_combo_box_index(int index);
    void set_test(int type, int distribution_type);
    void set_reject(bool value);
    void set_statistic(double value);
    void set_critical_value(double value);

    double get_significance_level();
    int get_combo_box_index();
    double get_critical_value();
    double get_statistic();
    shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> get_test();
    bool get_reject();

private:

    double significance_level;
    int combo_box_index;
    bool reject;
    double statistic;
    double critical_value;

    shared_ptr<StatisticalTest_AfterEVT<unsigned int, double>> test;

};

#endif // TESTPOSTMODEL_H






