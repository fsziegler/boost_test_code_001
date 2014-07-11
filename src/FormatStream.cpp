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
 * FormatStream.cpp
 *
 *  Created on: Jul 1, 2014
 *      Author: fred
 */

#include "FormatStream.h"
#include <string>
#include <set>
#include <deque>
#include <assert.h>

using namespace std;
namespace FormatStream {

enum State {
   kOn=0,
   kOff=1,
};

enum Colors {
   kBlack=0,
   kRed=1,
   kGreen=2,
   kYellow=3,
   kBlue=4,
   kPurple=5,
   kCyan=6,
   kWhite=7,
};

class TextAttr {
public:
   State bold_state;
   State underline_state;
   State inverse_state;
   TextAttr():
      bold_state(kOff),
      underline_state(kOff),
      inverse_state(kOff)
   {}
};

class SurroundAttr {
public:
   State background_state;
   State hi_intensity_state;
   SurroundAttr():
      background_state(kOff),
      hi_intensity_state(kOff)
   {}
};

typedef set<string> StrSet;
typedef StrSet::const_iterator StrSetCItr;

const int history_array_size(5);

// === <CFormatStream> =========================================================

class CFormatStream {
public:
   CFormatStream();
   ~CFormatStream();

   void EnableColors(bool new_state);
   void EnableDebug(bool new_state);
   const char* Bold(State new_state);
   const char* Underline(State new_state);
   const char* Inverse(State new_state);
   const char* Background(State new_state);
   const char* HiIntensity(State new_state);
   const char* Color(Colors new_color);
   const char* GetCode();
private:
   bool colors_enabled;
   bool debug_enabled;
   TextAttr prev_attr;
   TextAttr curr_attr;
   SurroundAttr prev_surr;
   SurroundAttr curr_surr;
   Colors color_state;
   StrSet history_set;
   const char* history_array[history_array_size];

   const char* GetTextCode() const;
   const char* GetSurroundCode() const;
   const char* GetFormatCode();

   CFormatStream(const CFormatStream&);
   CFormatStream(const CFormatStream&&);
   CFormatStream& operator=(const CFormatStream&);
   bool operator==(const CFormatStream&);
   bool operator!=(const CFormatStream&);
};

CFormatStream::CFormatStream() :
   colors_enabled(false),
   debug_enabled(false),
   color_state(kWhite)
{
}

CFormatStream::~CFormatStream() {
}

void CFormatStream::EnableColors(bool new_state) {
   colors_enabled = new_state;
}

void CFormatStream::EnableDebug(bool new_state) {
   debug_enabled = new_state;
}

const char* empty_str = "";
const char* CFormatStream::Bold(State new_state) {
   if(colors_enabled) {
      prev_attr = curr_attr;
      curr_attr.bold_state = new_state;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::Underline(State new_state) {
   if(colors_enabled) {
      curr_attr.underline_state = new_state;
      prev_attr = curr_attr;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::Inverse(State new_state) {
   if(colors_enabled) {
      prev_attr = curr_attr;
      curr_attr.inverse_state = new_state;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::Background(State new_state) {
   if(colors_enabled) {
      prev_surr = curr_surr;
      curr_surr.background_state = new_state;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::HiIntensity(State new_state) {
   if(colors_enabled) {
      prev_attr = curr_attr;
      curr_surr.hi_intensity_state = new_state;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::Color(Colors new_color) {
   if(colors_enabled) {
      color_state = new_color;
      return GetFormatCode();
   }
   return empty_str;
}

const char* CFormatStream::GetCode() {
   return GetFormatCode();
}

const string noformat_code =  "\033[0";
const string b_code        =  "\033[1";
const string u_code        =  "\033[4";
const string i_code        =  "\033[7";
const string end_code      =  "m";
const string delimit_code  =  ";";
void PopulateQueue(State state, const string& str, deque<string>& stack) {
   if(kOn == state) {
      stack.push_front(str);
   }
}

const char* CFormatStream::GetTextCode() const {
   // Not thread safe
   static string tmpstr;
   tmpstr.clear();
   deque<string> stack;
   PopulateQueue(kOn, noformat_code, stack);
   PopulateQueue(curr_attr.bold_state, b_code, stack);
   PopulateQueue(curr_attr.underline_state, u_code, stack);
   PopulateQueue(curr_attr.inverse_state, i_code, stack);
   while (1 < stack.size()) {
      tmpstr += stack.back();
      tmpstr += end_code;
      stack.pop_back();
   }
   tmpstr += stack.back();
   tmpstr += delimit_code;
   return tmpstr.c_str();
}

const string nosurr_code = "3";
const string bg_code     = "4";
const string hi_code     = "9";
const string bghi_code   = "10";
const char* CFormatStream::GetSurroundCode() const {
   const bool bg = (kOn == curr_surr.background_state);
   const bool hi = (kOn == curr_surr.hi_intensity_state);
   if(bg && hi) {
      return bghi_code.c_str();
   } else if (!bg && !hi) {
      return nosurr_code.c_str();
   }
   return (bg ? bg_code.c_str() : hi_code.c_str());
}

const string color_code[] { "0", "1", "2", "3", "4", "5", "6", "7", };
const char* CFormatStream::GetFormatCode() {
   // Not thread safe
   static string tmpstr;
   tmpstr.clear();
   if(colors_enabled) {
      tmpstr = GetTextCode();             // e.g., "\033[0m\033[1m\033[4;"
      tmpstr += GetSurroundCode();        // e.g., "40"
      tmpstr += color_code[color_state];  // e.g., "3"
      tmpstr += end_code;                 // "m"

      if(debug_enabled) {
         StrSetCItr itr = history_set.insert(tmpstr).first;
         for(int i= history_array_size-1; i > 0; --i) {
            history_array[i] = history_array[i-1];
         }
         history_array[0] = (*itr).c_str();
      }
      return tmpstr.c_str();
   }
   return empty_str;
}

// === </CFormatStream> ========================================================

CFormatStream fs;
const string  Color_Off="\033[0m";      // Text Reset
const char* s_reset() {
   return Color_Off.c_str();
}

void enableColors(bool state) {
   fs.EnableColors(state);
}

void enableDebug(bool state) {
   fs.EnableDebug(state);
}

const char* s_boldOn() {
   fs.Bold(kOn);
   return fs.GetCode();
}

const char* s_boldOff() {
   fs.Bold(kOff);
   return fs.GetCode();
}

const string  Underline_On="\033[4m";
const char* s_ulineOn() {
   fs.Underline(kOn);
   return fs.GetCode();
}

const char* s_ulineOff() {
   fs.Underline(kOff);
   return fs.GetCode();
}

const char* s_invOn() {
   fs.Inverse(kOn);
   return fs.GetCode();
}

const char* s_invOff() {
   fs.Inverse(kOff);
   return fs.GetCode();
}

const char* s_bckgndOn() {
   fs.Background(kOn);
   return fs.GetCode();
}

const char* s_bckgndOff() {
   fs.Background(kOff);
   return fs.GetCode();
}

const char* s_intensOn() {
   fs.HiIntensity(kOn);
   return fs.GetCode();
}

const char* s_intensOff() {
   fs.HiIntensity(kOff);
   return fs.GetCode();
}

// Colors
const char* s_black() {
   fs.Bold(kOff);
   fs.Color(kBlack);
   return fs.GetCode();
}

const char* s_dkGray() {
   fs.Bold(kOn);
   fs.Color(kBlack);
   return fs.GetCode();
}

const char* s_red() {
   fs.Bold(kOff);
   fs.Color(kRed);
   return fs.GetCode();
}

const char* s_ltRed() {
   fs.Bold(kOn);
   fs.Color(kRed);
   return fs.GetCode();
}

const char* s_green() {
   fs.Bold(kOff);
   fs.Color(kGreen);
   return fs.GetCode();
}

const char* s_ltGreen() {
   fs.Bold(kOn);
   fs.Color(kGreen);
   return fs.GetCode();
}

const char* s_brown() {
   fs.Bold(kOff);
   fs.Color(kYellow);
   return fs.GetCode();
}
const char* s_yellow() {
   fs.Bold(kOn);
   fs.Color(kYellow);
   return fs.GetCode();
}

const char* s_blue() {
   fs.Bold(kOff);
   fs.Color(kBlue);
   return fs.GetCode();
}

const char* s_ltBlue() {
   fs.Bold(kOn);
   fs.Color(kBlue);
   return fs.GetCode();
}

const char* s_purple() {
   fs.Bold(kOff);
   fs.Color(kPurple);
   return fs.GetCode();
}

const char* s_ltPurple() {
   fs.Bold(kOn);
   fs.Color(kPurple);
   return fs.GetCode();
}

const char* s_cyan() {
   fs.Bold(kOff);
   fs.Color(kCyan);
   return fs.GetCode();
}

const char* s_ltCyan() {
   fs.Bold(kOn);
   fs.Color(kCyan);
   return fs.GetCode();
}

const char* s_ltGray() {
   fs.Bold(kOff);
   fs.Color(kWhite);
   return fs.GetCode();
}

const char* s_white() {
   fs.Bold(kOn);
   fs.Color(kWhite);
   return fs.GetCode();
}

}

