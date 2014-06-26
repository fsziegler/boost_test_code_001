#include "BoostStringTextProc.h"

// <Array>
#include <boost/array.hpp>
#include <array>
// </Array>

// <Chrono>
#include <boost/chrono.hpp>
#include <boost/chrono/duration.hpp>
#include <boost/chrono/system_clocks.hpp>
//#include <boost/type_traits.hpp>
// </Chrono>

// <Random>
#include <boost/random/linear_congruential.hpp>
#include <boost/random/uniform_int.hpp>
#include <boost/random/uniform_real.hpp>
#include <boost/random/variate_generator.hpp>
#include <boost/generator_iterator.hpp>

typedef boost::minstd_rand base_generator_type;
// </Random>

using namespace std;
using namespace boost;

void Array() {
   const size_t len = 1E6;
   typedef boost::array<float, (const size_t) len>::iterator BAryItr;
   typedef boost::array<float, (const size_t) len>::reverse_iterator BAryRItr;
   typedef std::array<float, (const size_t) len>::iterator AryItr;
   typedef std::array<float, (const size_t) len>::reverse_iterator AryRItr;

   cout << "Perform Array tests" << endl;
   cout << "Testing Boost & C++11 Array" << endl;
   boost::array<float, (const size_t) len> boost_tst_array;
   std::array<float, (const size_t) len> tst_array;
   cout << "Boost Array size = " << boost_tst_array.size() << endl;
   cout << "C++11 Array size = " << tst_array.size() << endl;

   base_generator_type generator(42);
   boost::uniform_real<> uni_dist(0, 1);
   boost::variate_generator<base_generator_type&, boost::uniform_real<> > uni(
         generator, uni_dist);

   boost::chrono::duration<double> sec;
   chrono::steady_clock::time_point start = chrono::steady_clock::now();
   // Forward Iteration Test
   std::cout.setf(std::ios::fixed);
   for (size_t i = 0; i < len; ++i) {
      boost_tst_array[i] = uni();
      tst_array[i] = uni();
   }

   size_t i(0);
   for (BAryItr itr = boost_tst_array.begin(); itr < boost_tst_array.end();
         ++itr) {
      ++i;
   }
   assert(len == i);
   size_t j(0);
   for (AryItr itr = tst_array.begin(); itr < tst_array.end(); ++itr) {
      ++j;
   }
   assert(len == j);
   sec = boost::chrono::steady_clock::now() - start;
   cout << "Forward Array iterations succeeded [took " << sec.count() << " seconds]" << endl;

   // Reverse Iteration Test
   for (BAryRItr itr = boost_tst_array.rbegin(); itr < boost_tst_array.rend();
         ++itr) {
      --i;
   }
   assert(0 == i);
   for (AryRItr itr = tst_array.rbegin(); itr < tst_array.rend();
         ++itr) {
      --j;
   }
   assert(0 == j);
   sec = boost::chrono::steady_clock::now() - start;
   cout << "Reverse Array iterations succeeded [took " << sec.count() << " seconds]" << endl;

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
