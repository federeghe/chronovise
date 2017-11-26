#ifndef EVT_EVTAPPROACH_BM_HPP_
#define EVT_EVTAPPROACH_BM_HPP_

template <typename T>
class EVTApproach_BM : public EVTApproach {

public:
	virtual void perform(const MeasuresPool<T_INPUT, T_TIME>& original_pool);

};

#endif
