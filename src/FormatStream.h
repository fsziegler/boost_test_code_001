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
