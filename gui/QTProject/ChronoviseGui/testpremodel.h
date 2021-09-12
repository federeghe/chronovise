#ifndef TESTPREMODEL_H
#define TESTPREMODEL_H


using namespace std;

#include <string>

#include "statistical/test_ljung_box.hpp"
#include "statistical/test_rs.hpp"
#include "statistical/test_kpss.hpp"
#include "statistical/test_bds.hpp"
using namespace chronovise;


class TestPreModel
{
public:
    TestPreModel();
    void set_significance_level(double value);
    void set_combo_box_index(int value);
    void set_trend_class(string str);

    void set_ljungBox_test(double significance_level, int n_lags);
    void set_rs_test(double significance_level);
    void set_bds_test(double significance_level);
    void set_kpss_test(double significance_level, int lags, string trend);

    void set_statistic(double value);
    void set_reject(bool value);
    void set_critical_value(double value);
    void set_n_lags(unsigned int n_lags);

    double get_significance_level();
    int get_combo_box_index();
    string get_trend_class();

    TestLjungBox<unsigned int, double>* get_ljungBox_test();
    TestRS<unsigned int, double>* get_rs_test();
    TestBDS<unsigned int, double>* get_bds_test();
    TestKPSS<unsigned int, double>* get_kpss_test();

    double get_critical_value();
    double get_statistic();
    bool get_reject();
    unsigned int get_n_lags();

    ~TestPreModel();

private:
    double significance_level;
    int combo_box_index;
    string trend_class;
    unsigned int n_lags;

    TestLjungBox<unsigned int, double>* ljungBox_test;
    TestRS<unsigned int, double>* rs_test;
    TestKPSS<unsigned int, double>* kpss_test;
    TestBDS<unsigned int, double>* bds_test;

    double statistic;
    double critical_value;
    bool reject;




};

#endif // TESTPREMODEL_H
