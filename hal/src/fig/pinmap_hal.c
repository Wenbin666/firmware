/**
 ******************************************************************************
  Copyright (c) 2013-2014 IntoRobot Team.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation, either
  version 3 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, see <http://www.gnu.org/licenses/>.
  ******************************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "pinmap_hal.h"
#include "pinmap_impl.h"
#include <stddef.h>

#define GPIO0                      0     // GPIO_NUM_0
#define GPIO1                      1     // GPIO_NUM_1
#define GPIO2                      2     // GPIO_NUM_2
#define GPIO3                      3     // GPIO_NUM_3
#define GPIO4                      4     // GPIO_NUM_4
#define GPIO5                      5     // GPIO_NUM_5
#define GPIO6                      6     // GPIO_NUM_6
#define GPIO7                      7     // GPIO_NUM_7
#define GPIO8                      8     // GPIO_NUM_8
#define GPIO9                      9     // GPIO_NUM_9
#define GPIO10                     10
#define GPIO11                     11
#define GPIO12                     12
#define GPIO13                     13
#define GPIO14                     14
#define GPIO15                     15
#define GPIO16                     16
#define GPIO17                     17
#define GPIO18                     18
#define GPIO19                     19
#define GPIO20                     20
#define GPIO21                     21
#define GPIO22                     22
#define GPIO23                     23
#define GPIO24                     24
#define GPIO25                     25
#define GPIO26                     26
#define GPIO27                     27
#define GPIO28                     28
#define GPIO29                     29
#define GPIO30                     30
#define GPIO31                     31
#define GPIO32                     32
#define GPIO33                     33
#define GPIO34                     34 /* input mode only */
#define GPIO35                     35 /* input mode only */ 
#define GPIO36                     36 /* input mode only */
#define GPIO37                     37 /* input mode only */
#define GPIO38                     38 /* input mode only */
#define GPIO39                     39 /* input mode only */

/* #define GPIO_PinSource0            ((uint8_t)0x00) */
/* #define GPIO_PinSource1            ((uint8_t)0x01) */
/* #define GPIO_PinSource2            ((uint8_t)0x02) */
/* #define GPIO_PinSource3            ((uint8_t)0x03) */
/* #define GPIO_PinSource4            ((uint8_t)0x04) */
/* #define GPIO_PinSource5            ((uint8_t)0x05) */
/* #define GPIO_PinSource6            ((uint8_t)0x06) */
/* #define GPIO_PinSource7            ((uint8_t)0x07) */
/* #define GPIO_PinSource8            ((uint8_t)0x08) */
/* #define GPIO_PinSource9            ((uint8_t)0x09) */
/* #define GPIO_PinSource10           ((uint8_t)0x0A) */
/* #define GPIO_PinSource11           ((uint8_t)0x0B) */
/* #define GPIO_PinSource12           ((uint8_t)0x0C) */
/* #define GPIO_PinSource13           ((uint8_t)0x0D) */
/* #define GPIO_PinSource14           ((uint8_t)0x0E) */
/* #define GPIO_PinSource15           ((uint8_t)0x0F) */
/* #define GPIO_PinSource16           ((uint8_t)0x10) */


/* #define ADC_Channel_0  ((uint8_t)0x00) */
/* #define TIM1           ((uint8_t)0x00) */

/* Private typedef -----------------------------------------------------------*/

EESP32_Pin_Info __PIN_MAP[TOTAL_PINS] =
{
/*
 * gpio_pin (0-16)
 * gpio_pin_source (GPIO_PinSource0 - GPIO_PinSource15)
 * timer_peripheral (TIM1 - TIM5, or NONE)
 * timer_ch (1-3, or NONE)
 * pin_mode (NONE by default, can be set to OUTPUT, INPUT, or other types)
 */

/* D0            - 00 */ { GPIO19, NONE, NONE, NONE, PIN_MODE_NONE },
/* D1            - 01 */ { GPIO23, NONE, NONE, NONE, PIN_MODE_NONE },
/* D2            - 02 */ { GPIO18, NONE, NONE, NONE, PIN_MODE_NONE },
/* D3            - 03 */ { GPIO17, NONE, NONE, NONE, PIN_MODE_NONE },
/* D4            - 04 */ { GPIO16, NONE, NONE, NONE, PIN_MODE_NONE },
/* D5            - 05 */ { GPIO5,  NONE, NONE, NONE, PIN_MODE_NONE },
/* D6            - 06 */ { GPIO4, NONE, NONE, NONE, PIN_MODE_NONE },
/* D7            - 07 */ { GPIO4, NONE, NONE, NONE, PIN_MODE_NONE },
/* TX            - 08 */ { GPIO1,  NONE, NONE, NONE, PIN_MODE_NONE },
/* RX            - 09 */ { GPIO3,  NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 10 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 11 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 12 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 13 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
/* A0            - 14 */ { GPIO36, NONE, NONE, NONE, PIN_MODE_NONE },
/* A1            - 15 */ { GPIO39, NONE, NONE, NONE, PIN_MODE_NONE },
/* A2            - 16 */ { GPIO35, NONE, NONE, NONE, PIN_MODE_NONE },
/* A3            - 17 */ { GPIO25, NONE, NONE, NONE, PIN_MODE_NONE },
/* A4            - 18 */ { GPIO26, NONE, NONE, NONE, PIN_MODE_NONE },
/* A5            - 19 */ { GPIO15, NONE, NONE, NONE, PIN_MODE_NONE },
/* A6            - 20 */ { GPIO14, NONE, NONE, NONE, PIN_MODE_NONE },
/* A7            - 21 */ { GPIO12, NONE, NONE, NONE, PIN_MODE_NONE },
/* A8            - 22 */ { GPIO13,  NONE, NONE, NONE, PIN_MODE_NONE },
/* A9            - 23 */ { GPIO2,  NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 24 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
/* NOT USED      - 25 */ { NONE,   NONE, NONE, NONE, PIN_MODE_NONE },
};

EESP32_Pin_Info* HAL_Pin_Map() {
    return __PIN_MAP;
}
