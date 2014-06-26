#include "BoostStringTextProc.h"
#include <iostream>
#include <memory>
#include <assert.h>

using namespace std;
//cout << "Perform Array tests" << endl;

void Array() {
   assert(__cplusplus >= 201103L);
   int len = 7;
   auto text = std::unique_ptr<char[]>(new char[len]);
   cout << "Perform Array tests" << endl;
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
