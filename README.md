# eMBPTA
Measurement-Based Probabilistic Timing Analysis framework

What you need
=============
* `ceres-solver` installed (both libraries and header files). You can use one of the distribution package -- e.g. [Ubuntu](https://packages.ubuntu.com/search?keywords=libceres-dev), [Fedora](https://admin.fedoraproject.org/pkgdb/package/rpms/ceres-solver/), [Arch Linux](https://aur.archlinux.org/packages/ceres-solver/) -- or build it from the source. Please check the [ceres-solver documentation](http://ceres-solver.org/installation.html).
* A modern compiler like GCC or LLVM. C++11 support is needed (this should not be a problem with an updated distribution).
* The code should be cross-platform, however I could test it only on Linux. Please fill a bug if it does not work with other operating systems.

How to build it
===============
```bash
$ git clone https://github.com/federeghe/eMBPTA.git
$ cd eMBPTA
$ mkdir build
$ cd build
$ cmake ..
$ make
```

