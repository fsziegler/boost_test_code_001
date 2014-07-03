# Instructions for building the Boost libraries
* These instructions are from [Boost's "Getting Started on Unix Variants"](http://www.boost.org/doc/libs/1_55_0/more/getting_started/unix-variants.html), but also we want Boost to include OpenMPI, Python support, and bzip file compression support, which enables every aspect of Boost. **You may skip steps 1, 2, and/or 3 if you do not want the associated capability.**<br>

##Instructions for installing the Boost Libraries:<br>
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

