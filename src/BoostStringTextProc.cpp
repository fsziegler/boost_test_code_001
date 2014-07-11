/*
Copyright (c) 2014 Frederick S. Ziegler

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/
#include "BoostStringTextProc.h"
#include "FormatStream.h"
using namespace FormatStream;

// <Array>
#include <boost/array.hpp>
#include <array>
// </Array>

// <Chrono>
#include <boost/chrono.hpp>
// </Chrono>

// <Random>
#include <boost/random/linear_congruential.hpp>
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-local-typedefs"
#include <boost/random/uniform_real.hpp>
#pragma GCC diagnostic pop
#include <boost/random/variate_generator.hpp>

typedef boost::minstd_rand base_generator_type;
// </Random>

using namespace std;
using namespace boost;

void OutputFormattedTestName(const char* test_name) {
   cout << s_ltGray() << endl;
   cout << s_boldOn() << s_ulineOn() << test_name << endl;
   cout << s_boldOff() << s_ulineOff();
}

void OutputFormattedBoostDescription(const char* desc_text) {
   cout << s_cyan() << s_intensOn() << desc_text << endl;
   cout << "Quote from http://www.boost.org/doc/libs/." << endl;
   cout << s_intensOff() << s_ltGray();
}

void Array() {
   const size_t len = pow(2, 18);
   typedef boost::array<float, (const size_t) len>::iterator BAryItr;
   typedef boost::array<float, (const size_t) len>::reverse_iterator BAryRItr;
   typedef std::array<float, (const size_t) len>::iterator AryItr;
   typedef std::array<float, (const size_t) len>::reverse_iterator AryRItr;

   cout.imbue(std::locale(""));  // Causes formatted numbers with commas
   OutputFormattedTestName("Perform Array tests");
   OutputFormattedBoostDescription("Boost::Array: \"STL compliant container "
         "wrapper for arrays of constant size.\"");
   cout << "Testing Boost, C++11, and standard C Arrays of size ";
   cout << s_ltCyan() << len << endl;

   static boost::array<float, (const size_t) len> boost_tst_array;
   std::array<float, (const size_t) len> tst_array;

   float c_array[len];
   cout.setf(ios_base::fixed);
   cout << s_reset() << "     Boost Array size = " << s_ltCyan()
         << boost_tst_array.size() << endl;
   cout << s_reset() << "     C++11 Array size = " << s_ltCyan()
         << tst_array.size() << endl;
   cout << s_reset() << "standard C array size = " << s_ltCyan()
         << tst_array.size() << endl;
   cout << s_reset();

   base_generator_type generator(42);
   uniform_real<> uni_dist(0, 1);
   variate_generator<base_generator_type&, uniform_real<> > uni(generator,
         uni_dist);

   // Forward Iteration Test
   std::cout.setf(std::ios::fixed);
   for (size_t i = 0; i < len; ++i) {
      boost_tst_array[i] = uni();
      tst_array[i] = uni();
      c_array[i] = uni();
   }

   float val(0.0);
   size_t i(0);
   chrono::duration<double> sec;
   chrono::steady_clock::time_point start = chrono::steady_clock::now();
   for (BAryItr itr = boost_tst_array.begin(); itr < boost_tst_array.end();
         ++itr) {
      val = (*itr) / 2;
      *itr = val * 2;
      ++i;
   }
   assert(len == i);
   sec = chrono::steady_clock::now() - start;
   cout << "\t     Forward iteration of Boost Array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   size_t j(0);
   start = chrono::steady_clock::now();
   for (AryItr itr = tst_array.begin(); itr < tst_array.end(); ++itr) {
      val = (*itr) / 2;
      *itr = val * 2;
      ++j;
   }
   assert(len == j);
   sec = chrono::steady_clock::now() - start;
   cout << "\t     Forward iteration of C++11 Array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   size_t k(0);
   start = chrono::steady_clock::now();
   for (size_t x = 0; x < len; ++x) {
      val = c_array[x] / 2;
      c_array[x] = val * 2;
      ++k;
   }
   assert(len == k);
   sec = chrono::steady_clock::now() - start;
   cout << "\tForward iteration of standard C array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   cout << "Forward Array iterations succeeded!" << endl;

   // Reverse Iteration Test
   start = chrono::steady_clock::now();
   for (BAryRItr itr = boost_tst_array.rbegin(); itr < boost_tst_array.rend();
         ++itr) {
      val = (*itr) / 2;
      *itr = val * 2;
      --i;
   }
   assert(0 == i);
   sec = chrono::steady_clock::now() - start;
   cout << "\t     Reverse iteration of Boost Array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   start = chrono::steady_clock::now();
   for (AryRItr itr = tst_array.rbegin(); itr < tst_array.rend(); ++itr) {
      val = (*itr) / 2;
      *itr = val * 2;
      --j;
   }
   assert(0 == j);
   sec = chrono::steady_clock::now() - start;
   cout << "\t     Reverse iteration of C++11 Array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   start = chrono::steady_clock::now();
   sec = chrono::steady_clock::now() - start;
   cout << "\tReverse iteration of standard C array took " << s_ltCyan()
         << sec.count() * 1000;
   cout << s_ltGreen() << " milliseconds" << s_reset() << endl;

   cout << "Reverse Array iterations succeeded!" << endl;
}

void Bind() {
   OutputFormattedTestName("Perform Bind tests");
   OutputFormattedBoostDescription("Boost::Bind: \"a generalization of the "
         "standard functions std::bind1st and std::bind2nd. It supports "
         "arbitrary function objects, functions, function pointers, and member "
         "function pointers, and is able to bind any argument to a specific "
         "value or route input arguments into arbitrary positions.\"");
//   Using bind with functions and function pointers
//   Using bind with function objects
//   Using bind with pointers to members
//   Using nested binds for function composition
//   Overloaded operators (new in Boost 1.33)
//   Using bind with standard algorithms (Example)
//   Using bind with Boost.Function (Example)
}

void Function() {
   OutputFormattedTestName("Function tests");
   OutputFormattedBoostDescription("Boost::Function: \".\"");
   cout << "The Boost Function is used in this test code to store the test "
         "function to be called for each command line option. See the "
         "OptionFunctionMap.h file for its usage." << endl;
}

void Functional_Hash() {
   OutputFormattedTestName("Perform Functional/Hash tests");
   OutputFormattedBoostDescription("Boost::Functional/Hash: \"A TR1 hash "
         "function object that can be extended to hash user defined types.\"");
}

void Member_Function() {
   OutputFormattedTestName("Perform Member Function tests");
   OutputFormattedBoostDescription("Boost::Member Function: \"Generalized "
         "binders for function/object/pointers and member functions.\"");
}

void Random() {
   OutputFormattedTestName("Perform Random tests");
   OutputFormattedBoostDescription("Boost::Random: \"A complete system for "
         "random number generation.\"");
}

void Ref() {
   OutputFormattedTestName("Perform Ref tests");
   OutputFormattedBoostDescription("Boost::Ref: \"A utility library for "
         "passing references to generic functions.\"");
}

void Regex() {
   OutputFormattedTestName("Perform Regex tests");
   OutputFormattedBoostDescription(
         "Boost::Regex: \"Regular expression library.\"");
}

void Smart_Ptr() {
   OutputFormattedTestName("Perform Smart Ptr tests");
   OutputFormattedBoostDescription(
         "Boost::Smart Ptr: \"Smart pointer class templates.\"");
}

void TR1() {
   OutputFormattedTestName("Perform TR1 tests");
   OutputFormattedBoostDescription("Boost::TR1 Library: \"provides an "
         "implementation of the C++ Technical Report on Standard Library "
         "Extensions. This library does not itself implement the TR1 "
         "components, rather it's a thin wrapper that will include your "
         "standard library's TR1 implementation (if it has one), otherwise it "
         "will include the Boost Library equivalents, and import them into "
         "namespace std::tr1.\"");
}

void Tuple() {
   OutputFormattedTestName("Perform Tuple tests");
   OutputFormattedBoostDescription("Boost::Tuple: \"Ease definition of "
         "functions returning multiple values, and more.\"");
}

void Type_Traits() {
   OutputFormattedTestName("Perform Type Traits tests");
   OutputFormattedBoostDescription("Boost::Type Traits: \"Templates for "
         "fundamental properties of types.\"");
}

void Unordered() {
   OutputFormattedTestName("Perform Unordered tests");
   OutputFormattedBoostDescription(
         "Boost::Unordered: \"Unordered associative containers.\"");
}

void InitOptionFunctionMap(TOptFuncMap& optFuncMap) {
   optFuncMap.insert(TOptFuncPair(string("Array"), &Array));
   optFuncMap.insert(TOptFuncPair(string("Bind"), &Bind));
   optFuncMap.insert(TOptFuncPair(string("Function"), &Function));
   optFuncMap.insert(TOptFuncPair(string("FunctHash"), &Functional_Hash));
   optFuncMap.insert(TOptFuncPair(string("MemFunc"), &Member_Function));
   optFuncMap.insert(TOptFuncPair(string("Random"), &Random));
   optFuncMap.insert(TOptFuncPair(string("Ref"), &Ref));
   optFuncMap.insert(TOptFuncPair(string("Regex"), &Regex));
   optFuncMap.insert(TOptFuncPair(string("SmartPtr"), &Smart_Ptr));
   optFuncMap.insert(TOptFuncPair(string("TR1"), &TR1));
   optFuncMap.insert(TOptFuncPair(string("Tuple"), &Tuple));
   optFuncMap.insert(TOptFuncPair(string("TypeTraits"), &Type_Traits));
   optFuncMap.insert(TOptFuncPair(string("Unordered"), &Unordered));
}

//optFuncMap.insert(TOptFuncPair(string("Bind"), &Bind));
//optFuncMap.insert(TOptFuncPair(string("Function"), &Function));
//optFuncMap.insert(TOptFuncPair(string("Functional_Hash"), &Functional_Hash));
//optFuncMap.insert(TOptFuncPair(string("Member_Function"), &Member_Function));
//optFuncMap.insert(TOptFuncPair(string("Random"), &Random));
//optFuncMap.insert(TOptFuncPair(string("Ref"), &Ref));
//optFuncMap.insert(TOptFuncPair(string("Regex"), &Regex));
//optFuncMap.insert(TOptFuncPair(string("Smart_Ptr"), &Smart_Ptr));
//optFuncMap.insert(TOptFuncPair(string("TR1"), &TR1));
//optFuncMap.insert(TOptFuncPair(string("Tuple"), &Tuple));
//optFuncMap.insert(TOptFuncPair(string("Type_Traits"), &Type_Traits));
//optFuncMap.insert(TOptFuncPair(string("Unordered"), &Unordered));
