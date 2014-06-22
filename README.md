boost_test_code_001
===================

Programs to test and demonstrate Boost library capabilities

This code base is intended to contain all the code required to load, build, and run the test programs using Eclipse CDT. It has been developeed using the Kepler version of Eclipse, g++ 4.8.2, Boost 1.55, OpenMPI 1.8.1, and was developed using Kubuntu 14.04.

Instructions for installing boost:

https://github.com/fsziegler/boost_test_code_001

Instructions are from http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html, but also we want Boost to include OpenMPI, Python support, and file compression (libbz2) support.
Download boost_w_xy_z.tar.gz, extract it into its own directory (e.g., ~/dev/boost_1_55_0), and cd to there
Get the Python version (python --version) and install its development tools (e.g., sudo apt-get install python2.7-dev)
aptitude search python | grep dev will show all dev packages for Python
Install the latest libbz library (e.g., sudo apt-get install libbz2-dev)
aptitude search libbz | grep dev will show all dev packages for libbz
Download openmpi_w.x.y.tar.gz, extract it into its own directory (e.g., ~/dev/openmpi-1.8.1), and cd to there
sudo ./configure --prefix=/usr/local (takes tens of minutes)
sudo make all install (takes tens of minutes)
Run ./bootstrap.sh (takes tens of minutes)
gedit ./tools/build/v2/user-config.jam and append "using mpi ;" to it (including the space before ';')
document adding libraries, library order, library path, include path, linker flags (-static -lpthread)