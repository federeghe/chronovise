#ifndef STATISTICAL_ESTIMATOR_MLE_HPP_
#define STATISTICAL_ESTIMATOR_MLE_HPP_

#include "statistical/estimator.hpp"

#include <memory>


template <typename T_INPUT, typename T_TIME>
class Estimator_MLE : public Estimator<T_INPUT, T_TIME> {

public:

	virtual ~Estimator_MLE() {}

	virtual bool run(const MeasuresPool<T_INPUT, T_TIME> &measures) noexcept override;

	virtual EV_Distribution get_result() const override final {
		if (result == nullptr)
			throw std::runtime_error("Estimator never run");
		
		return *result;
	}

	virtual estimator_status_t get_status() const noexcept {
		return status;
	}	

private:
	std::shared_ptr<EV_Distribution> result;
	estimator_status_t status=UNKNOWN;

};

#endif
