# chronovise-gui

**chronovise-gui** provides a GUI for the chronovise framework.

What you need
-------------
The UI is written using QT framework, therefore a version of [QT library](https://www.qt.io/offline-installers) must to be installed (version used 5.12) with QtCharts module. 

Building
--------

It's needed to install chronovise library.

```bash
$ git clone https://github.com/federeghe/chronovise.git
$ cd chronovise
$ mkdir build
$ cd build
$ cmake ..
$ make
$ sudo make install
```

Once chronovise is installed:

```bash
$ cd gui
$ mkdir build
$ cd build
$ cmake ..
$ make
```