#ifndef STATISTICAL_EV_DISTRIBUTION_HPP_
#define STATISTICAL_EV_DISTRIBUTION_HPP_



class EV_Distribution {

public:
	explicit EV_Distribution() noexcept
	: param_location(0), param_scale(1), param_shape(0)
	{
	}

	explicit EV_Distribution(double location, double scale, double shape) noexcept
	:  param_location(location), param_scale(scale), param_shape(shape)
	{		
	}

	double get_location() const noexcept {
		return this->param_location;
	}

	double get_scale() const noexcept {
		return this->param_scale;
	}

	double get_shape() const noexcept {
		return this->param_shape;
	}

	bool is_gumbell() const noexcept {
		return this->param_shape == 0.0;
	}

	bool is_weibull() const noexcept {
		return this->param_shape < 0.0;
	}

	bool is_frechet() const noexcept {
		return this->param_shape > 0.0;
	}

	
private:
	const double param_location;
	const double param_scale;
	const double param_shape;

};


#endif	// STATISTICAL_EV_DISTRIBUTION_HPP_
