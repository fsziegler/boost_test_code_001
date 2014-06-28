//============================================================================
// Name        : boost_program_options_test.cpp
// Author      : Fred Ziegler
// Version     :
// Copyright   : Copyright 2014 Frederick S. Ziegler
// Description : Test code for various Boost libraries
//============================================================================

#include <boost/program_options.hpp>

namespace po = boost::program_options;
#include "OptionFunctionMap.h"
#include "BoostStringTextProc.h"
#include "ZiegVersion.h"
#include "PrintFormats.h"

using namespace std;
using namespace PrintFormats;

int main(int ac, char* av[]) {
   enableColors(false);
   TOptFuncMap optFuncMap;
   InitOptionFunctionMap(optFuncMap);

   try {
      po::options_description basic_opts("Generic options");
      basic_opts.add_options()
         ("version,v", "print version string")
         ("help","produce help message")
         ("color","show colors")
      ;

      po::options_description tr1_opts("TR1 options");
      tr1_opts.add_options()
         ("Array,a","STL compliant container wrapper for arrays of constant size.")
         ("Bind,b","boost::bind is a generalization of the standard functions std::bind1st and std::bind2nd.")
         ("Function,f","Function object wrappers for deferred calls or callbacks.")
         ("FunctHash,h","A TR1 hash function object that can be extended to hash user defined types.")
         ("MemFunc,m","Generalized binders for function/object/pointers and member functions.")
         ("Random,n", "A complete system for random number generation.")
         ("Ref,r","A utility library for passing references to generic functions.")
         ("Regex,x", "Regular expression library.")
         ("SmartPtr,p","Smart pointer class templates.")
         ("TR1,1","The TR1 library provides an implementation of the C++ Technical Report on Standard Library Extensions.")
         ("Tuple,l","Ease definition of functions returning multiple values, and more.")
         ("TypeTraits,t", "Templates for fundamental properties of types.")
         ("Unordered,u", "Unordered associative containers.")
      ;

      po::options_description str_txt_opts(
            "String and text processing options");
      str_txt_opts.add_options()
         ("Conversion","Polymorphic and lexical casts.")
         ("Format","The format library provides a class for formatting arguments according to a format-string")
         ("Iostreams","Boost.IOStreams provides a framework for defining streams, stream buffers and i/o filters.")
         ("Lexical Cast","General literal text conversions, such as an int represented a string, or vice-versa.")
         ("Locale","Provide localization and Unicode handling tools for C++.")
//         ("Regex,x", "Regular expression library.")
         ("Spirit","LL parser framework represents parsers directly as EBNF grammars in inlined C++.")
         ("String Algo", "String algorithms library.")
         ("Tokenizer","Break of a string or other character sequence into a series of tokens.")
         ("Wave","The Boost.Wave library implements the mandated C99/C++ preprocessor functionality.")
         ("Xpressive","Regular expressions that can be written as strings or as expression templates.")
      ;

      po::options_description cmdline_options;
      cmdline_options.add(basic_opts).add(tr1_opts).add(str_txt_opts);
      po::variables_map vm;
      po::store(po::parse_command_line(ac, av, cmdline_options), vm);
      po::notify(vm);

      if (vm.count("color")) {
         enableColors(true);
      }

      if (vm.count("help")) {
         cout << cmdline_options << endl;
         return 0;
      }

      if(201103L <= __cplusplus) {
         cout << boldOn() << "*** Using C++11 or better :-) ***" << boldOff() << endl;
      } else {
         cout << boldOn() << "*** Using C++ < C++11 :-( ***" << boldOff() << endl;
      }

      if (vm.count("version")) {
         cout << boldOn() << "   Version: " << ltCyan() << ZiegVersion::GetFullVersionString() << reset() << endl;
         cout << boldOn() << "Build Date: " << ltCyan() << ZiegVersion::BuildDate << reset() << endl;
         cout << boldOn() << "Build Time: " << ltCyan() << ZiegVersion::BuildTime << reset() << endl;
         cout << boldOn() << "      UUID: " << ltCyan() << ZiegVersion::UUID << reset() << endl;
      }

      if (vm.count("color")) {
         enableColors(true);
         cout << boldOn() << ltGreen() << "Colors:" << reset() << endl;
         cout << "Black DkGray Red LtRed Green LtGreen Brown Yellow Blue "
               "Purple LtPurple LtBlue Cyan LtCyan LtGray White" << endl;
         cout << black()      << "Black ";
         cout << dkGray()     << "DkGray ";
         cout << red()        << "Red ";
         cout << ltRed()      << "LtRed ";
         cout << green()      << "Green ";
         cout << ltGreen()    << "LtGreen ";
         cout << brown()      << "Brown ";
         cout << yellow()     << "Yellow ";
         cout << blue()       << "Blue ";
         cout << purple()     << "Purple ";
         cout << ltPurple()   << "LtPurple ";
         cout << ltBlue()     << "LtBlue ";
         cout << cyan()       << "Cyan ";
         cout << ltCyan()     << "LtCyan ";
         cout << ltGray()     << "LtGray ";
         cout << white()      << "White" << endl;
         cout << boldOn()     << "Bold text ";
         cout << boldOff()    << "Non-bold (normal) text" << endl;
         cout << reset() << endl;
      }

      TOptFuncMapCItr citr = optFuncMap.begin();
      while(optFuncMap.end() != citr) {
         TOptFuncPair optPair = (*citr);
         if (vm.count(optPair.first)) {
            TFuncPtr func = optPair.second;
            func();
         }
         ++citr;
      }
      return 0;
   }

   catch (exception& e) {
      cerr << "error: " << e.what() << "\n";
      return 1;
   } catch (...) {
      cerr << "Exception of unknown type!\n";
   }

   return 0;
}
