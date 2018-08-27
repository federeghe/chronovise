Sample applications
===================

Under `samples/` directory you could find two applications: `hello_world` and `simple_hello_world`.
The first one is using the AbstractExecutionContext, the second one the SimpleExecutionContext. If
this is the first time you use the framework, you should start from the latter one.

Simple Hello World
------------------
This test application is composed of three files:
 - `simple_main.cpp` containing the main()
 - `simple_hello_world.hpp` containing the header definition of extended SimpleExecutionContext class.
 - `simple_hello_world.cpp` containing the implementation of the extended SimpleExecutionContext class.

The main file is usually simple: just create your object and execute the run() method.

This example draws some time sample for an i.i.d. normal distribution with mean=12.0 and stddev=1.0.
The input value is not used and the input generator has been consequently set to zero. The exit
condition from the inner cycle is `AEC_SLOTH` leaving the framework to decide when sufficient samples
are acquired. Since the input values are not significant, the outer loop is execute only one time (check
the exit condition in onConfigure()).

The onRelease function prints a couple of examples of pWCET calculation.

Hello World
-----------
This test application is composed of three files:
 - `main.cpp` containing the main()
 - `hello_world.hpp` containing the header definition of extended AbstractExecutionContext class.
 - `hello_world.cpp` containing the implementation of the extended AbstractExecutionContext class.

**WARNING (1)**: this application is compiled ONLY IF `ceres-solver` is installed, since it uses MLE estimator.

**WARNING (2)**: this application will probably and on purpose fail to get a pWCET estimation. Read below.

This is a more advanced example compared to the previous one. In this case, the user can specify custom
objects derivated from the abstract classes to implement tests, estimators, input generators, etc. This
makes the syntax of using directly AbstractExecutionContext more verbose and less readable, compared to
the SimpleExecutionContext.

In this case the samples are acquired directly measuring the execution time of a C function after clearing
the cache. However, in modern computer architecture this doesn't guarantee the i.i.d. assumption and for
this reason if you execute this code in a standard x86[_64] machine the i.i.d. test will probably reject
the samples. This is expected and leads the framework to be unable to produce a reliable pWCET.

Other examples of usage
-----------------------
In the `samples` folder you can find also a couple of other examples:
 - `simple_hello_world_cv.cpp`
 - `simple_hello_world_cv_2.cpp`

both are variant of the described `simple_hello_world` that uses the MBPTA-CV approach. The difference
is that the version `simple_hello_world_cv` uses a normal distribution to produce data, while the
`simple_hello_world_cv_2` version uses a file as source.

