#ifndef EVTAPPROACHMODEL_H
#define EVTAPPROACHMODEL_H

using namespace std;
#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
#include <memory>

using namespace chronovise;

class EVTApproachModel
{
public:
    EVTApproachModel();
    ~EVTApproachModel()=default;


    void set_combo_box_index(int index);
    void set_approach(int type);
    void set_block_size(size_t block_size);
    void set_threshold(double threshold);
    void set_samples_test_reserve(float reserve);

    int get_combo_box_index();
    unique_ptr<EVTApproach<unsigned int, double>> get_approach();
    size_t get_block_size();
    double get_threshold();
    float get_samples_test_reserve();



private:
    int combo_box_index;
    size_t block_size;
    double threshold;
    float samples_test_reserve;
    unique_ptr<EVTApproach<unsigned int, double>> approach;



};

#endif // EVTAPPROACHMODEL_H
