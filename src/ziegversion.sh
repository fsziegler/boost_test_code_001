#!/bin/sh
#
#        File: ziegversion.sh
#  Created on: Jun 26, 2014
#      Author: Fred Ziegler
# Copyright 2014 Frederick S. Ziegler

sed -i -r 's/(const long int BuildNumber = )([0-9]+)/echo \1$((\2+1))/ge' ../src/ZiegVersion.h
sed -i -r "s/(const long int BuildNumber = )([0-9]+)/   const long int BuildNumber = \2;/g" ../src/ZiegVersion.h
sed -i -r "s/const long int UTCSeconds = [0-9]+;/const long int UTCSeconds = $(date +%s);/g" ../src/ZiegVersion.h
sed -i -r "s/const string BuildDate = \"[0-9\-]+\";/const string BuildDate = \"$(date +%F)\";/g" ../src/ZiegVersion.h
sed -i -r "s/const string BuildTime = \"[0-9\:]+\";/const string BuildTime = \"$(date +%T)\";/g" ../src/ZiegVersion.h
sed -i -r "s/const string UUID = \"[0-9a-z\-]+\";/const string UUID = \"$(uuid)\";/g" ../src/ZiegVersion.h
cat ../src/ZiegVersion.h
pwd
