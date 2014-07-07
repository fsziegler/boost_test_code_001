//============================================================================
// Name        : boost_program_options_test.cpp
// Author      : Fred Ziegler
// Version     :
// Copyright   : Copyright 2014 Frederick S. Ziegler
// Description : Test code for various Boost libraries
//============================================================================

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/program_options.hpp>
#pragma GCC diagnostic pop
#include <deque>
#include <string>

namespace po = boost::program_options;
#include "OptionFunctionMap.h"
#include "BoostStringTextProc.h"
#include "ZiegVersion.h"
#include "FormatStream.h"

using namespace std;
using namespace FormatStream;

typedef deque<string> StrDeque;
typedef StrDeque::const_iterator StrDequeCItr;
void populateDeque(bool bold, bool uline, bool inv, bool bckgnd, bool intens,
      StrDeque& outstrs) {
   if (bold) {
      outstrs.push_front("Bold");
   }
   if (uline) {
      outstrs.push_front("Underline");
   }
   if (inv) {
      outstrs.push_front("Inverse");
   }
   if (bckgnd) {
      outstrs.push_front("Background");
   }
   if (intens) {
      outstrs.push_front("Hi Intensity");
   }
   if(!bold && !uline && !inv && !bckgnd && !intens) {
      outstrs.push_front("Normal");
   }
}

void PopulateOStream(StrDeque& str_deque, ostream &out_strm) {
   for(StrDequeCItr itr = str_deque.begin(); itr != str_deque.end(); ++itr) {
      out_strm << (*itr) << " ";
   }
}

const string::size_type GetStreamLen(StrDeque& str_deque) {
   stringstream str_strm;
   PopulateOStream(str_deque, str_strm);
   return str_strm.str().size();

}

void printCombo(bool bold, bool uline, bool inv, bool bckgnd, bool intens,
      const char* (*color_func)(), ostream& out_strm) {

   StrDeque max_deque, str_deque;
   populateDeque(true, true, true, true, true, max_deque);
   populateDeque(bold, uline, inv, bckgnd, intens, str_deque);
   const string::size_type maxlen = GetStreamLen(max_deque);
   const string::size_type strlen = GetStreamLen(str_deque);
   // Print normal mode first
   for(string::size_type i = 0; i < (maxlen - strlen); ++i) {
      out_strm << " ";
   }
   (*color_func)();
   PopulateOStream(str_deque, out_strm);

   if (bold) {
      out_strm << s_boldOn();
   }
   if (uline) {
      out_strm << s_ulineOn();
   }
   if (inv) {
      out_strm << s_invOn();
   }
   if (bckgnd) {
      out_strm << s_bckgndOn();
   }
   if (intens) {
      out_strm << s_intensOn();
   }

   (*color_func)();
   PopulateOStream(str_deque, out_strm);
   out_strm << s_boldOff();
   out_strm << s_ulineOff();
   out_strm << s_invOff();
   out_strm << s_reset();
   out_strm << s_bckgndOff();
   out_strm << s_intensOff();
   out_strm << endl;
}

void CycleOutputFormats(const char* (*color_func)(), const char* color_str,
      ostream& out_strm) {
   out_strm << s_reset() << endl << color_str << " ";
   out_strm << s_boldOn() << s_ulineOn() << (*color_func)() << color_str << endl;
   out_strm << s_boldOff() << s_ulineOff() << s_reset();
   for (int bold = 0; bold < 2; ++bold) {
      for (int uline = 0; uline < 2; ++uline) {
         for (int inverse = 0; inverse < 2; ++inverse) {
            for (int bckgnd = 0; bckgnd < 2; ++bckgnd) {
               for (int intens = 0; intens < 2; ++intens) {
                  printCombo((1 == bold), (1 == uline), (1 == inverse),
                        (1 == bckgnd), (1 == intens), color_func, out_strm);
               }
            }
         }
      }
   }
}

int main(int ac, char* av[]) {
   enableDebug(true);
   TOptFuncMap optFuncMap;
   InitOptionFunctionMap(optFuncMap);

   try {
      po::options_description basic_opts("Generic options");
      basic_opts.add_options()
         ("version,v", "print version string")
         ("help","produce help message")
         ("color","show colors")
         ("extcolor","show extended color & formatting")
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

      if (vm.count("color") || vm.count("extcolor")) {
         enableColors(true);
      }

      if (vm.count("help")) {
         cout << cmdline_options << endl;
         return 0;
      }

      if (201103L <= __cplusplus) {
         cout << s_boldOn() << "*** Using C++11 or better :-) ***"
               << s_boldOff() << endl;
      } else {
         cout << s_boldOn() << "*** Using C++ < C++11 :-( ***" << s_boldOff()
               << endl;
      }

      if (vm.count("version")) {
         cout << s_ltCyan() << "   Version: ";
         cout << s_yellow() << ZiegVersion::GetFullVersionString() << endl;
         cout << s_ltCyan() << "Build Date: ";
         cout << s_yellow() << ZiegVersion::BuildDate << endl;
         cout << s_ltCyan() << "Build Time: ";
         cout << s_yellow() << ZiegVersion::BuildTime << endl;
         cout << s_ltCyan() << "      UUID: ";
         cout << s_yellow() << ZiegVersion::UUID << endl;
      }

      if (vm.count("extcolor")) {
         cout << s_boldOn() << s_ulineOn() << s_ltGreen() << "Colors:" << endl;
         cout << s_ulineOff() << s_reset();
         cout << "Black DkGray Red LtRed Green LtGreen Brown Yellow Blue "
               "LtBlue Purple LtPurple Cyan LtCyan LtGray White" << endl;
         cout << s_black()      << "Black ";
         cout << s_dkGray()     << "DkGray ";
         cout << s_red()        << "Red ";
         cout << s_ltRed()      << "LtRed ";
         cout << s_green()      << "Green ";
         cout << s_ltGreen()    << "LtGreen ";
         cout << s_brown()      << "Brown ";
         cout << s_yellow()     << "Yellow ";
         cout << s_blue()       << "Blue ";
         cout << s_ltBlue()     << "LtBlue ";
         cout << s_purple()     << "Purple ";
         cout << s_ltPurple()   << "LtPurple ";
         cout << s_cyan()       << "Cyan ";
         cout << s_ltCyan()     << "LtCyan ";
         cout << s_ltGray()     << "LtGray ";
         cout << s_white()      << "White" << endl;
         cout << s_boldOn()     << "      Bold text";
         cout << s_boldOff()    << " Non-bold (normal) text" << endl;
         cout << s_ulineOn()    << "Underlined text";
         cout << s_ulineOff()   << " Non-underlined (normal) text" << endl;
         cout << s_invOn()      << "  Inverted text";
         cout << s_invOff()     << " Non-inverted (normal) text" << endl;
         cout << s_reset() << endl;

         CycleOutputFormats(&s_black, "Black", cout);
         CycleOutputFormats(&s_red, "Red", cout);
         CycleOutputFormats(&s_green, "Green", cout);
         CycleOutputFormats(&s_brown, "Yellow", cout);  // yellow is bold brown
         CycleOutputFormats(&s_blue, "Blue", cout);
         CycleOutputFormats(&s_purple, "Purple", cout);
         CycleOutputFormats(&s_cyan, "Cyan", cout);
         CycleOutputFormats(&s_ltGray, "White", cout);  // white is bold lt grey

         cout << endl << "Note: If you see garbage characters, then your "
               "terminal does not support colors." << endl << endl;
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
