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
    ~TestPostModel();
    void set_significance_level(double value);
    void set_combo_box_index(int index);
    void set_ks_test(double significance_level,int distribution_type);
    void set_ad_test(double significance_level, int distribution_type, bool mad);
    void set_cvm_test(double significance_level,int distribution_type);
    void set_reject(bool value);


    double get_significance_level();
    int get_combo_box_index();
    TestKS<unsigned int, double>* get_ks_test();
    TestAD<unsigned int, double>* get_ad_test();
    TestCvM<unsigned int, double>* get_cvm_test();
    bool get_reject();

private:

    double significance_level;
    int combo_box_index;
    bool reject;
    TestKS<unsigned int, double>* ks_test;
    TestAD<unsigned int, double>* ad_test;
    TestCvM<unsigned int, double>* cvm_test;

};

#endif // TESTPOSTMODEL_H






