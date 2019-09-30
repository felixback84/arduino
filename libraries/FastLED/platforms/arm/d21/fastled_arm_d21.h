#ifndef __INC_FASTLED_ARM_D21_H
#define __INC_FASTLED_ARM_D21_H

#include "fastpin_arm_d21.h"
#include "clockless_arm_d21.h"

#endif


#elif defined(ARDUINO_SAMD_MKRWIFI1010)

#define MAX_PIN 22
_DEFPIN_ARM( 0, 0, 22); _DEFPIN_ARM( 1, 0, 23); _DEFPIN_ARM( 2, 0, 10); _DEFPIN_ARM( 3, 0, 11);
_DEFPIN_ARM( 4, 1, 10); _DEFPIN_ARM( 5, 1, 11); _DEFPIN_ARM( 6, 0, 20); _DEFPIN_ARM( 7, 0, 21);
_DEFPIN_ARM( 8, 0, 16); _DEFPIN_ARM( 9, 0, 17); _DEFPIN_ARM( 10, 0, 19); _DEFPIN_ARM( 11, 0, 8);
_DEFPIN_ARM( 12, 0, 9); _DEFPIN_ARM( 13, 1, 23); _DEFPIN_ARM( 14, 1, 22); _DEFPIN_ARM( 15, 0, 2);
_DEFPIN_ARM( 16, 1, 2); _DEFPIN_ARM( 17, 1, 3); _DEFPIN_ARM( 18, 0, 4); _DEFPIN_ARM( 19, 0, 5);
_DEFPIN_ARM( 20, 0, 6); _DEFPIN_ARM( 21, 0, 7);
#define SPI_DATA 8
#define SPI_CLOCK 9

#define HAS_HARDWARE_PIN_SUPPORT 1