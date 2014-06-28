/*
 * PrintFormats.cpp
 *
 *  Created on: Jun 27, 2014
 *      Author: fred
 */

// Good reference: http://en.wikipedia.org/wiki/ANSI_escape_code
#include "PrintFormats.h"

namespace PrintFormats {

const char boldCodes[2][5] = { { 27, '[', '1', 'm', '\0' }, // boldOn
      { 27, '[', '0', 'm', '\0' }, // boldOff (also, reset)
      };
const char codes[18][9] = {
//\033[01;34m
      { 27, '[', '0', '0', ';', '3', '0', 'm', '\0' },   // Black          0;30
      { 27, '[', '0', '1', ';', '3', '0', 'm', '\0' },   // Dark Gray      1;30
      { 27, '[', '0', '0', ';', '3', '1', 'm', '\0' },   // Red            0;31
      { 27, '[', '0', '1', ';', '3', '1', 'm', '\0' },   // Light Red      1;31
      { 27, '[', '0', '0', ';', '3', '2', 'm', '\0' },   // Green          0;32
      { 27, '[', '0', '1', ';', '3', '2', 'm', '\0' },   // Light Green    1;32
      { 27, '[', '0', '0', ';', '3', '3', 'm', '\0' },   // Brown          0;33
      { 27, '[', '0', '1', ';', '3', '3', 'm', '\0' },   // Yellow         1;33
      { 27, '[', '0', '0', ';', '3', '4', 'm', '\0' },   // Blue           0;34
      { 27, '[', '0', '1', ';', '3', '4', 'm', '\0' },   // Light Blue     1;34
      { 27, '[', '0', '0', ';', '3', '5', 'm', '\0' },   // Purple         0;35
      { 27, '[', '0', '1', ';', '3', '5', 'm', '\0' },   // Light Purple   1;35
      { 27, '[', '0', '0', ';', '3', '6', 'm', '\0' },   // Cyan           0;36
      { 27, '[', '0', '1', ';', '3', '6', 'm', '\0' },   // Light Cyan     1;36
      { 27, '[', '0', '0', ';', '3', '7', 'm', '\0' },   // Light Gray     0;37
      { 27, '[', '0', '1', ';', '3', '7', 'm', '\0' },   // White          1;37
      };

bool colors(true);
bool bold(true);

const char* reset() {
   return boldCodes[1];
}

void enableColors(bool state) {
   colors = state;
}

void enableBold(bool state) {
   bold = state;
}

char empty[] = { 7 };
const char* boldOn() {
   return (colors ? boldCodes[0] : boldCodes[1]);
}

const char* boldOff() {
   return boldCodes[1];
}

const char* black() {
   return (colors ? codes[0] : boldCodes[1]);
}

const char* dkGray() {
   return (colors ? codes[1] : boldCodes[1]);
}
const char* red() {
   return (colors ? codes[2] : boldCodes[1]);
}
const char* ltRed() {
   return (colors ? codes[3] : boldCodes[1]);
}
const char* green() {
   return (colors ? codes[4] : boldCodes[1]);
}
const char* ltGreen() {
   return (colors ? codes[5] : boldCodes[1]);
}
const char* brown() {
   return (colors ? codes[6] : boldCodes[1]);
}
const char* yellow() {
   return (colors ? codes[7] : boldCodes[1]);
}
const char* blue() {
   return (colors ? codes[8] : boldCodes[1]);
}
const char* purple() {
   return (colors ? codes[9] : boldCodes[1]);
}
const char* ltPurple() {
   return (colors ? codes[10] : boldCodes[1]);
}
const char* ltBlue() {
   return (colors ? codes[11] : boldCodes[1]);
}
const char* cyan() {
   return (colors ? codes[12] : boldCodes[1]);
}
const char* ltCyan() {
   return (colors ? codes[13] : boldCodes[1]);
}
const char* ltGray() {
   return (colors ? codes[14] : boldCodes[1]);
}
const char* white() {
   return (colors ? codes[15] : boldCodes[1]);
}

}
