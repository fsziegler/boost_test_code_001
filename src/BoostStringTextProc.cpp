#include "BoostStringTextProc.h"
//#include "PrintFormats.h"
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
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>

typedef boost::minstd_rand base_generator_type;
// </Random>

using namespace std;
using namespace boost;
//using namespace PrintFormats;

void Array() {
   const size_t len = pow(2, 18);
   typedef boost::array<float, (const size_t) len>::iterator BAryItr;
   typedef boost::array<float, (const size_t) len>::reverse_iterator BAryRItr;
   typedef std::array<float, (const size_t) len>::iterator AryItr;
   typedef std::array<float, (const size_t) len>::reverse_iterator AryRItr;

   cout.imbue(std::locale(""));  // Causes formatted numbers with commas
   cout << s_boldOn() << "Perform Array tests" << s_boldOff() << endl;
   cout << "Testing Boost, C++11, and standard C Arrays of size " << len
         << endl;

   static boost::array<float, (const size_t) len> boost_tst_array;
   std::array<float, (const size_t) len> tst_array;

   float c_array[len];
   cout.setf(ios_base::fixed);
   cout << "     Boost Array size = " << fixed << boost_tst_array.size()
         << endl;
   cout << "     C++11 Array size = " << tst_array.size() << endl;
   cout << "standard C array size = " << tst_array.size() << endl;

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
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

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
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

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
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

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
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

   start = chrono::steady_clock::now();
   for (AryRItr itr = tst_array.rbegin(); itr < tst_array.rend(); ++itr) {
      val = (*itr) / 2;
      *itr = val * 2;
      --j;
   }
   assert(0 == j);
   sec = chrono::steady_clock::now() - start;
   cout << "\t     Reverse iteration of C++11 Array took " << s_ltCyan()
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

   start = chrono::steady_clock::now();
   for (size_t x = len - 1; -1 > x; --x) {
      if (5 == x) {
         int q(8);
      }
      val = c_array[x] / 2;
      c_array[x] = val * 2;
      --k;
   }
   assert(0 == k);
   sec = chrono::steady_clock::now() - start;
   cout << "\tReverse iteration of standard C array took " << s_ltCyan()
         << sec.count() * 1000 << s_ltGray() << " milliseconds" << endl;

   cout << "Reverse Array iterations succeeded!" << endl;
}

void Bind() {
   cout << "Perform Bind tests" << endl;
}

void Function() {

   cout << "The Boost Function is used in this test code to store the test "
         "function to be called for each command line option. See the "
         "OptionFunctionMap.h file for its usage." << endl;
}

void Functional_Hash() {
   cout << "Perform Functional/Hash tests" << endl;
}

void Member_Function() {
   cout << "Perform Member Function tests" << endl;
}

void Random() {
   cout << "Perform Random tests" << endl;
}

void Ref() {
   cout << "Perform Ref tests" << endl;
}

void Regex() {
   cout << "Perform Regex tests" << endl;
}

void Smart_Ptr() {
   cout << "Perform Smart Ptr tests" << endl;
}

void TR1() {
   cout << "Perform TR1 tests" << endl;
}

void Tuple() {
   cout << "Perform Tuple tests" << endl;
}

void Type_Traits() {
   cout << "Perform Type Traits tests" << endl;
}

void Unordered() {
   cout << "Perform Unordered tests" << endl;
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
