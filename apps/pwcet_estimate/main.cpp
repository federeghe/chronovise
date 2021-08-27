#include "aec.hpp"
#include "pwcet_estimate.hpp"



int main() {

    chronovise::MeasuresPool<int, double> mp;    // Input values not used here, we randomly put int.

    double value;

    while (std::cin >> value)
    {
       mp.push(0, value);
    }

    chronovise::AbstractExecutionContext<unsigned int, double> *aec = new PWCET_Estimate(mp);
    aec->run();

    delete aec;

    return 0;
}
