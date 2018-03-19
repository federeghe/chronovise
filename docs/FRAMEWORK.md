The chronovise framework
========================

The **chronovise** framework provides a set of features to run the entire **Measurement-Based
Probabilistic Time Analysis (MBPTA)** process. The framework is built as a C++ static library
that can be linked to your implementation. Your implementation should implement the methods of
the abstract class provided by the framework, as subsequently described, in order to configure and
adapt the framework to your specific requirements.

AbstractExecutionContext (AEC)
------------------------------
The **AbstractExecutionContext (AEC)** is the main class of chronovise. This abstract class contains
the main logic of the MBPTA process and it should be extended by a user-provided class, implementing
the following methods:

- onSetup():     the initialization phase. The user application has to configure the framework in this
                 phase.
- onConfigure(): this method is called every time a new input is generated from chronovise. This is
                 to configure your application according to the new set of input provided.
- onRun():       the onRun method is executed every time to get a new sample. The used should put the
                 code to retrive the new sample here.
- onMonitor():   the function called each time after onRun(). It should be used for monitoring purposes
                 and it allows the user, via the return value, to specify the condition of exit (see
                 next section)
- onRelease():   eventually, a last method to clean stuffs and print output informations.


The execution flow can be depicted as follow:

```
  onSetup()
     |
     V
+-onConfigure() <-+
|    |            |
|    V            |
| onRun() <---+   | input
|    |        |   | change
|    V        |   |
| onMonitor()-+---+
|
V
onRelease()

```

For further details please check the diagrams in the `docs` subfolder.

### Exit conditions

The following exit codes are available for AEC methods (`AbstractExecutionContext::exit_code_t`):
- `AEC_OK`: the usual "done" or "successful" exit code. Returning this code in onConfigure()
            leads to the onRelease and subsequently the program termination.
- `AEC_CONTINUE`: the framework will repeat the action. For example, returning this code in onMonitor()
                  instructs the framework to do another round of onRun()-onMonitor(). Returning
                  this code in onConfigure() instructs the framework to perform MBPTA on the
                  current input.
- `AEC_SLOTH`: leave the decision to the framework according to evt approach and test characteristics
- `AEC_GENERIC_ERROR`: a generic error, abort the measurements.

### Template datatypes

Most of chronovise classes is based on this two template arguments:
- `T_INPUT`: any type (simple or class) that represents your input space.
- `T_TIME`: it must be a numerical simple type (like int, float, etc.) and it representes the data
            type of the timing measurements.

Currently, the following types are automatically compiled with chronovise:
- for `T_INPUT`: `char`, `int`, `long`, `float`, `double`, `unsigned char`, `unsigned int` `unsigned long`
- for `T_TIME`: `unsigned long`, `double`

If you need custom input types in `T_INPUT` or want to add a new value for `T_TIME`, you can modify
the macro `TEMPLATE_CLASS_IMPLEMENTATION` in `include/global.hpp`.

### Setup the framework
Besides the implementation of the required methods, the application must call the following methods in order
to configure the framework:
 - `set_input_source(...)`: to set the input generator that the framework will use to draw input sample. If the
                            application is not input dependent, please use the NullGenerator.
 - `set_merging_technique(...)`: select between ENVELOPE and MERGE tracing
 - `set_evt_approach(...)`: set the EVT approach to use. In the current version of the framework, BM and PoT are
                            already implemented.
 - `set_evt_estimator(...)`: set the EVT estimator to use to estimate the extreme distribution from the output of
                             the EVT approach. In chronovise there currently are two estimator: PWM and MLE. The
                             last one is available for BM only and it requires the ceres-solver package.
In addition to the previous mandatory items, the application can add some statistical tests at predefined hooks:
 - `add_input_representativity_test(...)`: add a test to check the representativity of the inputs. This is the
                                           only hook you can use to check T_INPUT data.
 - `add_sample_test(...)`: add a test on collected time values before proceeding to EVT. This is usually used to
                           check the i.i.d. or similar properties.
 - `add_post_approach_test(...)`: add a test to be executed after the EVT approach, i.e. after block-maxima or
                                  peak-over-threshold, but before the EVT estimation.
 - `add_post_evt_test(...)`: add a test on the estimated extreme-value distribution.

SimpleExecutionContext
----------------------

