/*
 * OptionFunctionMap.h
 *
 *  Created on: Jun 25, 2014
 *      Author: fred
 */

#ifndef OPTIONFUNCTIONMAP_H_
#define OPTIONFUNCTIONMAP_H_

#include <boost/function.hpp>
#include <map>
using namespace std;

typedef boost::function<void()> TFuncPtr;
typedef pair<string, TFuncPtr> TOptFuncPair;
typedef map<string, TFuncPtr> TOptFuncMap;
typedef TOptFuncMap::const_iterator TOptFuncMapCItr;

#endif /* OPTIONFUNCTIONMAP_H_ */
