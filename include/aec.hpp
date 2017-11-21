#ifndef AEC_HPP_
#define AEC_HPP_


#include <string>

class AbstractExecutionContext {

public:

	typedef enum {

		// Normal statuses
		AEC_OK = 0,
		AEC_CONTINUE,
		AEC_STOP,

		// Error statuses
		AEC_GENERIC_ERROR,

	} exit_code_t;

	virtual exit_code_t onSetup() noexcept = 0;
	virtual exit_code_t onConfigure() noexcept = 0;
	virtual exit_code_t onRun() noexcept = 0;
	virtual exit_code_t onMonitor() noexcept = 0;
	virtual exit_code_t onRelease() noexcept = 0;

	void run() noexcept;

protected:
	inline unsigned long get_iteration() {
		return iteration;
	}

private:
	unsigned long iteration = 0;

	void print_error(const std::string &s);

};

#endif
