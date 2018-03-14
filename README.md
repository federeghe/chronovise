# chronovise
![alt text](./docs/logo.svg "Logo Chronovise")

Measurement-Based Probabilistic Timing Analysis framework

Master branch: [![Build Status](https://travis-ci.com/federeghe/chronovise.svg?token=GZRsPDxBM5ANCBVx8AuB&branch=master)](https://travis-ci.com/federeghe/chronovise)

Development branch: [![Build Status](https://travis-ci.com/federeghe/chronovise.svg?token=GZRsPDxBM5ANCBVx8AuB&branch=master-next)](https://travis-ci.com/federeghe/chronovise)

This code is licensed under Apache-2.0, please refer to the LICENSE file.

What you need
=============
* A modern compiler like GCC or LLVM. C++14 support is needed (this is normally available in updated
  Linux distributions).

* The code should be **cross-platform** because we do not use any Linux-specific feature. However,
  we usually test it only on Linux. Please fill a bug if it does not work with other operating systems.

Dependencies:
* `ceres-solver` installed (both libraries and header files). You can use one of the distribution
  package -- e.g. [Ubuntu](https://packages.ubuntu.com/search?keywords=libceres-dev)*,
  [Fedora](https://admin.fedoraproject.org/pkgdb/package/rpms/ceres-solver/),
  [Arch Linux](https://aur.archlinux.org/packages/ceres-solver/) -- or build it from the source.
  Please check the [ceres-solver documentation](http://ceres-solver.org/installation.html).
* [optional] `Google Test` if you want to run the test suite.

\* Be aware that in Ubuntu the current package has a
   [dependency bug](https://launchpad.net/ubuntu/+source/ceres-solver/+bugs).

Building
========
To build the main library and the examples perform the standard `cmake` sequence of commands:
```bash
$ git clone https://github.com/federeghe/chronovise.git
$ cd chronovise
$ mkdir build
$ cd build
$ cmake ..
$ make
```

You can also enable OpenMP to speedup the process changing the `cmake` command to:

```
cmake -DUSE_OPENMP=ON ..
```

Test suite
----------
The test suite is based on [Google Test](https://github.com/google/googletest), so you need to
install it in your machine before proceeding. Then you can build the test suite:

```make tests```

and run them:

```make check```

This may take some minutes to complete. Please note that **occasionally** the test suite can fail:
some tests are based on random samples and it can infrequently happen that an unlikely configuration
occurs. This is typical of statistical tests that fails with a probability of 5\%. If the test suite
provides you a failure, please re-run it a couple of times to check that is not a random spot.
 

Run the examples
----------------
The framework is shipped with two example: **HelloWorld** and **SimpleHelloWorld**. The source
files are located under the ```samples/``` directory.
You can run them inside the `build` directory via:

```./samples/hello_world```

and

```./samples/simple_hello_world```

Please check the documentation for further details.

Documentation
=============
Please check [the documentation index file](docs/INDEX.md).

Development & Issue & Support
=============================
Can I contribute? Sure!

The code is hosted in mirroring on [GitHub](https://github.com/federeghe/chronovise) and
on a private university server. Please open any bug or pull request on the GitHub
repository. If you need support or you want to contribute please ask directly to the
head developer: Federico Reghenzani <federico[dot]reghenzani(at)polimi[dot].it>.
