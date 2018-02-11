#ifndef EVT_EVTAPPROACH_POT_HPP_
#define EVT_EVTAPPROACH_POT_HPP_

namespace chronovise {

template <typename T>
class EVTApproach_POT : public EVTApproach {

public:
	virtual void perform(const MeasuresPool<T_INPUT, T_TIME>& original_pool);

};

} // namespace chronovise

#endif
