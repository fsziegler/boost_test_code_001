/*
 * ZiegVersion.h
 *
 *  Created on: Jun 26, 2014
 *      Author: Fred Ziegler
 *  Copyright 2014 Frederick S. Ziegler
 *
 *  The purpose of this file is to record the latest version info for the rest
 *  of a code base. It is intended that the compiler run a bash shell script 
 *  that updates this using the following sed commands:
#!/bin/sh
#
#        File: ziegversion.sh
#  Created on: Jun 26, 2014
#      Author: Fred Ziegler
# Copyright 2014 Frederick S. Ziegler

sed -i -r 's/(long int BuildNumber = )([0-9]+)/echo \1$((\2+1))/ge' ../src/ZiegVersion.h
sed -i -r "s/(long int BuildNumber = )([0-9]+)/   long int BuildNumber = \2;/g" ../src/ZiegVersion.h
sed -i -r "s/long int UTCSeconds = [0-9]+;/long int UTCSeconds = $(date +%s);/g" ../src/ZiegVersion.h
sed -i -r "s/string BuildDate = \"[0-9\-]+\";/string BuildDate = \"$(date +%F)\";/g" ../src/ZiegVersion.h
sed -i -r "s/string BuildTime = \"[0-9\:]+\";/string BuildTime = \"$(date +%T)\";/g" ../src/ZiegVersion.h
sed -i -r "s/string UUID = \"[0-9a-z\-]+\";/string UUID = \"$(uuid)\";/g" ../src/ZiegVersion.h
 *
 */

#ifndef ZIEGVERSION_H_
#define ZIEGVERSION_H_

#include <string>

using namespace std;

namespace ZiegVersion
{
// These are not updated automatically
   string MajorVersion = "0";
   string MinorVersion = "0";

// These are updated automatically with each build
   long int BuildNumber = 1022;
   long int UTCSeconds = 1403850464;   // Updated with date +%s
   string BuildDate = "2014-06-26";    // Updated with date +%F
   string BuildTime = "23:27:44";      // Updated with date +%T
   string UUID = "26446e7a-fdc4-11e3-8dc6-bb62f11fc1eb"; // Updated with uuid
   
   string GetFullVersionString() {
      stringstream fullVersion;
      fullVersion << MajorVersion << "." << MinorVersion << "." << BuildNumber;
      return fullVersion.str();
   }
}

#endif /* ZIEGVERSION_H_ */