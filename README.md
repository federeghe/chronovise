# chronovise
<img align="right" alt="Logo Chronovise" width="150" height="150" src="./docs/logo.svg">

**chronovise** is a framework to perform Measurement-Based Probabilistic Timing Analyses (MBPTA).
MBPTA is a recent proposed technique in the field of probabilistic real-time computing, that
relies on execution time observations to infer the probabilistic Worst-Case Execution Time (pWCET).
The framework has been developed to be easily customizable and adaptable by the researcher for both
testing new MBPTA algorithms and evaluating the pWCET of a certain system/software.


|    Branch    | Description    | Status       |
|--------------|----------------|--------------|
| master       | Stable         | [![Build Status](https://travis-ci.org/federeghe/chronovise.svg?branch=master)](https://travis-ci.org/federeghe/chronovise) |
| master-next  | Development    | [![Build Status](https://travis-ci.org/federeghe/chronovise.svg?branch=master-next)](https://travis-ci.org/federeghe/chronovise) |
| master       | Coverage       | [![Coverage Status](https://coveralls.io/repos/github/federeghe/chronovise/badge.svg)](https://coveralls.io/github/federeghe/chronovise) |

What you need
-------------
* A modern compiler like GCC or LLVM. C++14 support is needed (this is normally available in updated
  Linux distributions).

* The code should be **cross-platform** because we do not use any Linux-specific feature. However,
  we usually test it only on Linux. Please fill a bug if it does not work with other operating systems.

Dependencies:
* [optional] `ceres-solver` installed (both libraries and header files). You can use one of the distribution
  package -- e.g. [Ubuntu](https://packages.ubuntu.com/search?keywords=libceres-dev)*,
  [Fedora](https://admin.fedoraproject.org/pkgdb/package/rpms/ceres-solver/),
  [Arch Linux](https://aur.archlinux.org/packages/ceres-solver/) -- or build it from the source.
  Please check the [ceres-solver documentation](http://ceres-solver.org/installation.html).
* [optional] `Google Test` if you want to run the test suite.

\* Be aware that the current Ubuntu package has a
   [dependency bug](https://launchpad.net/ubuntu/+source/ceres-solver/+bugs).

Building
--------
To build the main library and the examples perform the standard `cmake` sequence of commands:
```bash
$ git clone https://github.com/federeghe/chronovise.git
$ cd chronovise
$ mkdir build
$ cd build
$ cmake ..
```

If you do not have access to `ceres-solver` you can disable modules that depends on it specifying the
appropriate macro in cmake command:

```
$ cmake -DCERES_SOLVER=OFF ..
```

You can also enable OpenMP to speedup the process changing the `cmake` command to:

```
$ cmake -DUSE_OPENMP=ON ..
```

Then, to compile:

```
$ make
```

(you can also specify the appropriate `-j` option to decrease the compilation time).

### Test suite

The test suite is based on [Google Test](https://github.com/google/googletest), so you need to
install it in your machine before proceeding. Then you can build the test suite:

```make tests```

and run it:

```make check```

This may take some minutes to complete. Please note that **occasionally** the test suite can fail:
some tests are based on random samples and it can infrequently happen that an unlikely configuration
occurs. This is typical of statistical tests that fails with a probability of 5\%. If the test suite
provides you a failure, please re-run it a couple of times to check that is not a random spot.
 

Run the examples
----------------
The framework is shipped with two example automatically compiled with the framework: **HelloWorld**
and **SimpleHelloWorld**. The source files are located under the ```samples/``` directory. The
*HelloWorld* sample application is available only if ceres-solver is available.
You can run them inside the `build` directory via:

```./samples/hello_world```

and

```./samples/simple_hello_world```

Please check the documentation for further details.

Documentation
-------------
Please check [the documentation index file](docs/INDEX.md).

Development & Issue & Support
-----------------------------
Can I contribute? Sure!

The code is hosted in mirroring on [GitHub](https://github.com/federeghe/chronovise) and
on a private university server. All bug reports and pull requests must be open on the GitHub
repository. If you need support or you want to discuss new contributions please ask directly
to the head developer: Federico Reghenzani <federico[dot]reghenzani(at)polimi[dot]it>.

License
-------
This code is licensed under Apache-2.0, please refer to the LICENSE file.

The logo is a derivative work of the following original images [(1 - LGPL)](https://commons.wikimedia.org/wiki/File:Out_of_date_clock_icon.svg) and [(2 - Flaticon Basic)](https://www.flaticon.com/free-icon/vise_222459#term=vise&page=1&position=2).
