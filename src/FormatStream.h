/*
 * FormatStream.h
 *
 *  Created on: Jul 1, 2014
 *      Author: fred
 */

#ifndef FORMATSTREAM_H_
#define FORMATSTREAM_H_

namespace FormatStream {

   const char* s_reset();
   void enableColors(bool state);
   void enableDebug(bool state);

   const char* s_boldOn();
   const char* s_boldOff();
   const char* s_ulineOn();
   const char* s_ulineOff();
   const char* s_invOn();
   const char* s_invOff();

   const char* s_bckgndOn();
   const char* s_bckgndOff();
   const char* s_intensOn();
   const char* s_intensOff();

   // Colors
   const char* s_black();
   const char* s_dkGray();
   const char* s_red();
   const char* s_ltRed();
   const char* s_green();
   const char* s_ltGreen();
   const char* s_brown();
   const char* s_yellow();
   const char* s_blue();
   const char* s_ltBlue();
   const char* s_purple();
   const char* s_ltPurple();
   const char* s_cyan();
   const char* s_ltCyan();
   const char* s_ltGray();
   const char* s_white();

}

#endif /* FORMATSTREAM_H_ */
