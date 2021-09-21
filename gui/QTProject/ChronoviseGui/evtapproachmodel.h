#ifndef EVTAPPROACHMODEL_H
#define EVTAPPROACHMODEL_H

#include "evt/evtapproach_bm.hpp"
#include "evt/evtapproach_pot.hpp"
using namespace chronovise;

class EVTApproachModel
{
public:
    EVTApproachModel();
    ~EVTApproachModel();


    void set_combo_box_index(int index);
    void set_bm_approach(size_t block_size);
    void set_pot_approach(double threshold);
    void set_block_size(size_t block_size);
    void set_threshold(double threshold);
    void set_samples_test_reserve(float reserve);

    int get_combo_box_index();
    EVTApproach_BM<unsigned int, double>* get_bm_approach();
    EVTApproach_PoT<unsigned int, double>* get_pot_approach();
    size_t get_block_size();
    double get_threshold();
    float get_samples_test_reserve();

private:
    int combo_box_index;
    EVTApproach_BM<unsigned int, double>* bm_approach;
    EVTApproach_PoT<unsigned int, double>* pot_approach;
    size_t block_size;
    double threshold;
    float samples_test_reserve;


};

#endif // EVTAPPROACHMODEL_H
