#boost_test_code_001

##Programs to test and demonstrate the Boost C++ library capabilities

This [public GitHub repository](https://github.com/fsziegler/boost_test_code_001) is intended to contain all the instructions and code required to load, build, and run the test programs using Eclipse CDT. It has been developeed using the Kepler version of [**Eclipse CDT**](http://www.eclipse.org/cdt/downloads.php), [**g++**](https://gcc.gnu.org/) 4.8.2, [**Boost**](http://www.boost.org/users/download/) 1.55, [**OpenMPI**](http://www.open-mpi.org/software/ompi/v1.8/) 1.8.1, and was developed on the [**Kubuntu**](http://www.kubuntu.org/getkubuntu) 14.04 operating system.

##System preparation<br>
* Install Linux onto a computer. The commands listed here are for flavors of Debian Linux, which support the `apt-get` command for installing and updating software. I used [Kubuntu](http://www.kubuntu.org/getkubuntu), a variant of Debian Linux, to develop these instructions and code, as it has my favorite Linux GUI.<br>
* My practice is to create a single root directory for all libraries I will use to develop software. I create ~/dev for this (~/ is the Linux placeholder for /home/_username_/).<br>
 * `mkdir ~/dev`<br>
* These instructions are from [Boost's "Getting Started on Unix Variants"](http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html), but also we want Boost to include OpenMPI, Python support, and bzip file compression support, which enables every aspect of Boost. **You may skip steps 1, 2, and/or 3 if you do not want the associated capability.**<br>

##Instructions for installing Boost:<br>
1. Install the **[Python](https://www.python.org/)** development tools<br>
 * Find your Python version (`python --version`) and install its development tools (e.g., `sudo apt-get install python2.7-dev`)<br>
 * _`aptitude search python | grep dev` will show all dev packages for Python_<br>
2. Install the the latest **[bzip](http://www.bzip.org/)** library
 * e.g., run `sudo apt-get install libbz2-dev`<br>
 * _`aptitude search libbz | grep dev` will show all dev packages for libbz_<br>
3. Install the the latest **[OpenMPI](http://www.open-mpi.org/software/ompi/)** library
 * Download openmpi-_version_.tar.gz, extract it into its own directory (e.g., ~/dev/openmpi-1.8.1), and `cd` to there<br>
 * `sudo ./configure --prefix=/usr/local` _(this takes tens of minutes)_<br>
 * `sudo make all install` _(this takes tens of minutes)_<br>
4. Install the the latest **[Boost](http://www.boost.org/users/download/)** library
 * Download boost_ _version_.tar.gz, extract it into its own directory (e.g., ~/dev/boost_1_55_0), and cd to there<br>
 * Run `sudo ./bootstrap.sh` _(this takes tens of minutes)_<br>
 * If you performed step (3), then `gedit ./tools/build/v2/user-config.jam` and append "using mpi ;" to it (including the space before ';')<br>
 * Run `sudo ./b2` _(this takes tens of minutes)_<br>

##Instructions for configuring Eclipse<br>
* document adding libraries, library order, library path, include path, linker flags (-static -lpthread)<br>
