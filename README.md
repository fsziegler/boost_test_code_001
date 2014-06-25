#boost\_test\_code\_001

##Programs to test and demonstrate the Boost C++ library capabilities

This [public GitHub repository](https://github.com/fsziegler/boost_test_code_001) is intended to contain all the instructions and code required to load, build, and run the test programs using Eclipse CDT. It has been developeed using the Kepler version of [**Eclipse CDT**](http://www.eclipse.org/cdt/downloads.php), [**g++**](https://gcc.gnu.org/) 4.8.2, [**Boost**](http://www.boost.org/users/download/) 1.55, [**OpenMPI**](http://www.open-mpi.org/software/ompi/v1.8/) 1.8.1, and was developed on the [**Kubuntu**](http://www.kubuntu.org/getkubuntu) 14.04 operating system.

##System preparation<br>
* Install Linux onto a PC. The commands listed here are for flavors of Debian Linux, which support the `apt-get` command for installing and updating software. I used [Kubuntu](http://www.kubuntu.org/getkubuntu), a variant of Debian Linux, to develop these instructions and code, as it has my favorite Linux GUI.<br>
* Install the latest version of Eclipse CDT. See [this site](http://askubuntu.com/questions/26632/how-to-install-eclipse) for instructions on how to do this - apt-get and the Ubuntu Software Center tend to not have the latest versions.
* My practice is to create a single root directory for all libraries I will use to develop software. I create ~/dev for this (~/ is the Linux placeholder for /home/_username_/).<br>
 * `mkdir ~/dev`<br>
* These instructions are from [Boost's "Getting Started on Unix Variants"](http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html), but also we want Boost to include OpenMPI, Python support, and bzip file compression support, which enables every aspect of Boost. **You may skip steps 1, 2, and/or 3 if you do not want the associated capability.**<br>

##Instructions for installing Boost:<br>
1. Install the **[Python](https://www.python.org/)** development tools<br>
 * Find your Python version (`python --version`) and install its development tools (e.g., `sudo apt-get install python2.7-dev`)<br>
 * _`aptitude search python | grep dev` will show all dev packages for Python_<br>
2. Install the latest **[bzip](http://www.bzip.org/)** library
 * e.g., run `sudo apt-get install libbz2-dev`<br>
 * _`aptitude search libbz | grep dev` will show all dev packages for libbz_<br>
3. Install the latest **[OpenMPI](http://www.open-mpi.org/software/ompi/)** library
 * Download openmpi-_version_.tar.gz, extract it into its own directory (e.g., ~/dev/openmpi-1.8.1), and `cd` to there<br>
 * `sudo ./configure --prefix=/usr/local` _(this takes tens of minutes)_<br>
 * `sudo make all install` _(this takes tens of minutes)_<br>
4. Install the latest **[Boost](http://www.boost.org/users/download/)** library
 * Download boost\__version_.tar.gz, extract it into its own directory (e.g., ~/dev/boost\_1\_55\_0), and cd to there<br>
 * Run `sudo ./bootstrap.sh` _(this takes tens of minutes)_<br>
 * If you performed step (3), then `gedit ./tools/build/v2/user-config.jam` and append "using mpi ;" to it (including the space before ';')<br>
 * Run `sudo ./b2` _(this takes tens of minutes)_<br>

##Instructions for configuring Eclipse<br>
1. When creating a project in Eclipse that uses Boost, you must configure Eclipse to build with Boost. Select Project:Properties, which opens the Properties dialog box, and select "[All configurations]" in the Configuration field. _Be sure to do this each time you open the Properties dialog box_. Then:<br>
 * **Add the include path** for Boost. In the Properties dialog box select C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Compiler:Includes and add the path to the root of the Boost file installation; e.g., ~/dev/boost\_1\_55\_0.<br>
 * Under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Libraries: Library search path (-L) **add the path to the Boost libraries** you built. This is the stage/lib/ directory under the root Boost installation; e.g., ~/dev/boost\_1\_55\_0/stage/lib/.<br>
 * Under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Libraries:Libraries **add the name of each Boost library you will use**. If you are using the program_options library, the library file is "libboost\_program\_options.a," but the name to add is just "boost\_program\_options." Some Boost libraries do not require linking with a library, so do not worry if you do not see a library for the library you are using.<br>
 * Under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Miscellaneous **add "-static -lpthread" in the Linker flags** field.<br>
 * If you build your code and get an error such as: "typedef ‘boost_concept_check172’ locally defined but not used [-Wunused-local-typedefs], boost_program_options_test, line 71, external location: /home/.../general.hpp  C/C++ Problem," try (a) rebuilding the index: Project:C/C++ Index:Rebuild and (b) add the boost_system library under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Libraries:Libraries.
 * Note that experience seems to indicate that the order of the boost libraries under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Libraries:Libraries is important, and that the boost_system library should be at the bottom.
 
