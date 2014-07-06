#boost\_test\_code\_001

##Programs to test and demonstrate the Boost C++ library capabilities
###Background
The Boost libraries are a collection of very powerful, robust, and highly regarded C++ libraries. A [subset](http://www.boost.org/doc/libs/1_55_0/doc/html/boost_tr1.html) of the libraries was accepted into the C++ standard. Bjarne Stroustrup, the inventor of C++,  references the Boost libraries on [his web page about C++11](http://www.stroustrup.com/C++11FAQ.html).
###Purpose
This [public GitHub repository](https://github.com/fsziegler/boost_test_code_001) is intended to contain all the instructions and code required to load, build, and run the test programs using Eclipse CDT (**C/C++ Development Tools**). It has been developeed using the Kepler version of [**Eclipse CDT**](http://www.eclipse.org/cdt/downloads.php), [**g++**](https://gcc.gnu.org/) 4.8.2, [**Boost**](http://www.boost.org/users/download/) 1.55, [**OpenMPI**](http://www.open-mpi.org/software/ompi/v1.8/) 1.8.1, and was developed on the [**Kubuntu**](http://www.kubuntu.org/getkubuntu) 14.04 operating system.<br>

##System preparation<br>
* Install Linux onto a PC. The commands listed here are for flavors of Debian Linux, which support the `apt-get` command for installing and updating software. I used [Kubuntu](http://www.kubuntu.org/getkubuntu), a variant of Debian Linux, to develop these instructions and code, as it has my favorite Linux GUI.<br>
* Install the latest version of Eclipse CDT. See [this site](http://askubuntu.com/questions/26632/how-to-install-eclipse) for instructions on how to do this - apt-get and the Ubuntu Software Center tend to not have the latest versions.
* My practice is to create a single root directory for all libraries I will use to develop software. I create ~/dev for this (~/ is the Linux placeholder for /home/_username_/).<br>
 * `mkdir ~/dev`<br>hi	
* If you want to build the Boost libraries, instructions can be found [here](/https://github.com/fsziegler/boost_test_code_001/blob/master/Build Boost Libraries.md).
* These instructions are from [Boost's "Getting Started on Unix Variants"](http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html), but also we want Boost to include OpenMPI, Python support, and bzip file compression support, which enables every aspect of Boost. **You may skip steps 1, 2, and/or 3 if you do not want the associated capability.**<br>

##Instructions for installing the Boost Libraries:<br>
1. Install the latest **[bzip](http://www.bzip.org/)** library
 * e.g., run `sudo apt-get install libbz2-dev`<br>
 * _`aptitude search libbz | grep dev` will show all dev packages for libbz_<br>
2. Run `sudp apt-get install libboost1.55-all-dev` to install all of the Boost libraries.<br>

##Instructions for configuring Eclipse<br>
When creating a project in Eclipse that uses Boost, you must configure Eclipse to build with Boost. Select Project:Properties, which opens the Properties dialog box, and select "[All configurations]" in the Configuration field. _Be sure to do this each time you open the Properties dialog box_. Then:<br>
###Enable C++11 compilation<br>
 * In the Properties dialog box select C/C++ Build:Settings:[tab]Tool Settings:**GCC C++ Compiler:Miscellaneous** and add **" -std=c++11"** to the "Other flags field".<br>
 * Next, in C/C++ General:**Preprocessor Include Paths, Macros etc.**:[tab]**Providers** make sure that only the following options are selected:
  * CDT GCC Built-in Compiler Settings<br>
  * CDT GCC Build Output Parser<br>
  * CDT GCC Managed Build Setting Entries<br>
  * CDT User Setting Entries<br>
 * Select "CDT GCC Built-in Compiler Settings" and make sure that "**Use global provider shared between projects**" is unchecked, and in the field for "**Command to get compiler specs:**" append **" -std=c++11"**. Do this for both Debug and Release. _Note: the latter three options are required in order for the indexer to work properly._
 * Under C/C++ Build:Settings:[tab]Tool Settings:**GCC C++ Linker:Miscellaneous** add **"-static -lpthread -std=c++11" in the Linker flags** field.<br>
 * _You can check **whether or not C++11 has been enabled** by navigating to C/C++ General:General:Preprocessor Include Paths, Macros etc.:[tab]**Entries:GNU C++** and inspecting the value of #__cplusplus; if it has a value of 201103L or greater, C++11 is enabled, otherwise not._
 
###Add Boost library support<br>
 * **Add the include path** for Boost. In the Properties dialog box select C/C++ Build:Settings:[tab]Tool Settings:**GCC C++ Compiler:Includes** and add the path to the root of the Boost file installation; e.g., ~/dev/boost\_1\_55\_0.<br>
 * Under C/C++ Build:Settings:[tab]Tool Settings:**GCC C++ Linker:Libraries** Library search path (-L) **add the path to the Boost libraries** you built. This is the stage/lib/ directory under the root Boost installation; e.g., ~/dev/boost\_1\_55\_0/stage/lib/.<br>
 * Under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:**Libraries:Libraries** add **the name of each Boost library you will use**. For example, if you are using the program\_options library, the library file is "libboost\_program\_options.a," but the name to add is just "boost\_program\_options." Some Boost libraries do not require linking with a library, so do not worry if you do not see a library for the library you are using.<br>
 * Click Apply, then OK.
 * It is a good idea to restart Eclipse - **File:Restart**.
 * Select Project:**C/C++ Index:Rebuild**, and then Project:**C/C++ Index:Re-resolve unresolved includes**.
 * If you build your code and get an error such as: "typedef 'boost\_concept\_check172' locally defined but not used [-Wunused-local-typedefs], boost\_program\_options\_test, line 71, external location: /home/.../general.hpp  C/C++ Problem," try surrounding your Boost \#include-s as follows:<br>
 `#pragma GCC diagnostic push`<br>
 `#pragma GCC diagnostic ignored "-Wunused-local-typedefs"`<br>
 `// Your #includes here...`<br>
 `#include <boost/program_options.hpp>`<br>
 `#pragma GCC diagnostic pop`<br>
 * Note that when linking libraries statically, the order is important; if library A depends on symbols in library B, then library A should be listed before library B. You can set the order under C/C++ Build:Settings:[tab]Tool Settings:GCC C++ Linker:Libraries:Libraries. If you change or remove a library and get immediate compiler errors, try restarting Eclipse and doing a clean build.
 
###Miscellaneous<br>
 * Debugging STL structures is much easier if you use "pretty-printing" - see this [Eclipse Wiki](http://wiki.eclipse.org/CDT/User/FAQ#I.27ve_been_asked_for_.27gdb_traces.27.2C_where_can_I_find_them.3F) for instructions. When checking out the pretty printing script, replace "svn:" with "http:" - `svn co http://gcc.gnu.org/svn/gcc/trunk/libstdc++-v3/python`.<br>
  * You can find the location of the gdbinit file with `locate gdbinit`.
