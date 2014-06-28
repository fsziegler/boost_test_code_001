/*
 * PrintFormats.h
 *
 *  Created on: Jun 27, 2014
 *      Author: fred
 */

#ifndef PRINTFORMATS_H_
#define PRINTFORMATS_H_

namespace PrintFormats {
   const char* reset();
   void enableColors(bool state);
   void enableBold(bool state);

   const char* boldOn();
   const char* boldOff();
   const char* black();
   const char* dkGray();
   const char* red();
   const char* ltRed();
   const char* green();
   const char* ltGreen();
   const char* brown();
   const char* yellow();
   const char* blue();
   const char* purple();
   const char* ltPurple();
   const char* ltBlue();
   const char* cyan();
   const char* ltCyan();
   const char* ltGray();
   const char* white();
}

#endif /* PRINTFORMATS_H_ */
