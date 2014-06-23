//============================================================================
// Name        : boost_program_options_test.cpp
// Author      : Fred Ziegler
// Version     :
// Copyright   : Copyright 2014 Frederick S. Ziegler
// Description : Test code for various Boost libraries
// Id      $Id$
// Date    $Date$
// File    $File$
// Author  $Author$
// Rev.    $Revision$
// Src     $Source$
//============================================================================

#include <boost/program_options.hpp>
namespace po = boost::program_options;

#include <iostream>
#include <iterator>
#include <map>
using namespace std;

int boo()
{
   return 0;
}

int main(int ac, char* av[])
{
   boo();
   try {

       po::options_description desc("Allowed options");
       desc.add_options()
           ("help", "produce help message")
           ("compression", po::value<double>(), "set compression level")
       ;

       po::variables_map vm;
       po::variables_map foo;
       foo.count(string("foo"));
       po::store(po::parse_command_line(ac, av, desc), vm);
       po::notify(vm);

       if (vm.count("help")) {
           cout << desc << "\n";
           return 0;
       }

       if (vm.count("compression")) {
           cout << "Compression level was set to "
                << vm["compression"].as<double>() << ".\n";
       } else {
           cout << "Compression level was not set.\n";
       }
   }
   catch(exception& e) {
       cerr << "error: " << e.what() << "\n";
       return 1;
   }
   catch(...) {
       cerr << "Exception of unknown type!\n";
   }

   return 0;
}
