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
cat ../src/ZiegVersion.h
pwd