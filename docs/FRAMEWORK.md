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
- onMonitor():   the 
- onRelease():   eventually, a last method to clean stuffs and print output informations.


