//  kaimana_local.h

#ifndef __kaimana_local_h__
#define __kaimana_local_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"
#include "settings.h"

#define _START_DEFAULT_ANIMATION defaultStartup();
#define _START_WALK_ANIMATION walkyStartup(_IDLE_COLOR);
#define _START_STAR_ANIMATION starryStartup(_IDLE_COLOR);
#define _IDLE_DEFAULT animation_idle();
#define _IDLE_WALK_ANIMATION walkyIdle(_IDLE_COLOR);
#define _IDLE_STAR_ANIMATION starryIdle(_IDLE_COLOR);	
#define _IDLE_BREATHE_ANIMATION breatheSine(_IDLE_COLOR);
#define _IDLE_BREATHE_MAC_ANIMATION breatheApple(_IDLE_COLOR);

#ifdef _LED_ORDER_FULL
  // Map function names to Kaimana J2 LED index numbers 
  // KAIMANA -> LED_K4 -> LED_K3 -> LED_K2 -> LED_K1 -> LED_P4 -> LED_P3 -> LED_P2 -> LED_P1 -> LED_START -> LED_SELECT -> LED_TP -> LED_JOY
  // Neopixel LED ring uses two values for some reason:
  // LED_JOY_U     31, 32
  // LED_JOY_D     23, 24
  // LED_JOY_L     27, 28
  // LED_JOY_R     35, 36
  //
  #define  LED_JOY_U     32
  #define  LED_JOY_D     24
  #define  LED_JOY_L     28
  #define  LED_JOY_R     36
  #define  LED_P4      8
  #define  LED_P4_B    9
  #define  LED_P3      10
  #define  LED_P3_B    11
  #define  LED_P2      12
  #define  LED_P2_B    13
  #define  LED_P1      14
  #define  LED_P1_B    15
  #define  LED_K1      6
  #define  LED_K1_B    7
  #define  LED_K2      4
  #define  LED_K2_B    5
  #define  LED_K3      2
  #define  LED_K3_B    3
  #define  LED_K4      0
  #define  LED_K4_B    1  
  #define  LED_HOME    20
  #define  LED_HOME_B  21
  #define  LED_SELECT  18
  #define  LED_SELECT_B 19
  #define  LED_TP    22 // PS4 touchpad
  #define  LED_TP_B  23
  #define  LED_START   16
  #define  LED_START_B 17
  // maximum number of LEDs attached to Kaimana board
  #define  LED_COUNT   40
  #define  LED_JOY_RING 12
#endif

// general definitions for delays and other customizable features
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  BOOT_COLOR_DELAY         200    // value in miliseconds
#define  FAST_COLOR_DELAY         150    // value in miliseconds
#define  BOOT_COMPLETE_DELAY      500    // value in miliseconds
#define  MAIN_LOOP_DELAY           50    // value in miliseconds - used main loop
#define  IDLE_TIMEOUT_SECONDS       5    // value in seconds - normally 60 or 30 seconds but set very short for testing
#define  IDLE_ANIMATION_DELAY       5    // value in miliseconds - use smaller value for faster idle animation playback
#define  T_DELAY      			  250    

/*
// definitions of RGB values use by random color generator: setLEDRandomColor(int)
#define  COLOR_RANDOM_1    127,220,000    // lime green
#define  COLOR_RANDOM_2    127,000,220    // purple
#define  COLOR_RANDOM_3    000,220,220    // blue
#define  COLOR_RANDOM_4    000,255,127    // cyan
#define  COLOR_RANDOM_5    000,127,255    // cobalt blue
#define  COLOR_RANDOM_6    255,000,000    // red
#define  COLOR_RANDOM_7    245,113,012    // orange
#define  COLOR_RANDOM_8    220,000,127    // magenta
#define  COLOR_RANDOM_9	   177,037,075
*/

// definitions of RGB values use by random color generator: setLEDRandomColor(int)
#define  COLOR_RANDOM_1    RED    // lime green
#define  COLOR_RANDOM_2    ORANGE    // purple
#define  COLOR_RANDOM_3    YELLOW    // blue
#define  COLOR_RANDOM_4    GREEN    // cyan
#define  COLOR_RANDOM_5    CYAN    // cobalt blue
#define  COLOR_RANDOM_6    BLUE    // red
#define  COLOR_RANDOM_7    PURPLE    // orange
#define  COLOR_RANDOM_8    MAGENTA    // magenta  

// definitions for combo switch patterns
//
//   test for switches in reverse order (newest to oldest)
//
//   street figher 4 - ryu's special moves
//   http://www.eventhubs.com/guides/2008/jul/06/ryu-street-fighter-4-character-guide/
//

// 236 + P
#define  COMBO_PATTERN_1A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_1B    ATTACK_RIGHT + ATTACK_P2, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_1C    ATTACK_RIGHT + ATTACK_P3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN

// 214 + P
#define  COMBO_PATTERN_1D    ATTACK_LEFT + ATTACK_P1, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_1E    ATTACK_LEFT + ATTACK_P2, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_1F    ATTACK_LEFT + ATTACK_P3, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN

// 624 + P
#define  COMBO_PATTERN_2A    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P1, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_2B    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P2, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT
#define  COMBO_PATTERN_2C    ATTACK_DOWN + ATTACK_RIGHT + ATTACK_P3, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_RIGHT

// 421 + P
#define  COMBO_PATTERN_2D    ATTACK_DOWN + ATTACK_LEFT + ATTACK_P1, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_LEFT
#define  COMBO_PATTERN_2E    ATTACK_DOWN + ATTACK_LEFT + ATTACK_P2, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_LEFT
#define  COMBO_PATTERN_2F    ATTACK_DOWN + ATTACK_LEFT + ATTACK_P3, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN, ATTACK_NONE,  ATTACK_LEFT

// 214 + K
#define  COMBO_PATTERN_3A    ATTACK_LEFT + ATTACK_K1, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_3B    ATTACK_LEFT + ATTACK_K2, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN
#define  COMBO_PATTERN_3C    ATTACK_LEFT + ATTACK_K3, ATTACK_LEFT, ATTACK_DOWN + ATTACK_LEFT, ATTACK_DOWN

// 236 + K
#define  COMBO_PATTERN_3D    ATTACK_RIGHT + ATTACK_K1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_3E    ATTACK_RIGHT + ATTACK_K2, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_3F    ATTACK_RIGHT + ATTACK_K3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN

#define  COMBO_PATTERN_4A    ATTACK_RIGHT + ATTACK_P1, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_5A    ATTACK_RIGHT + ATTACK_P3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN
#define  COMBO_PATTERN_6A    ATTACK_RIGHT + ATTACK_K3, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN, ATTACK_NONE, ATTACK_RIGHT, ATTACK_DOWN + ATTACK_RIGHT, ATTACK_DOWN

//#define  START_MENU			 ATTACK_P4 + ATTACK_P3 
//#define  TOURNAMENT_MODE     	ATTACK_P4 + ATTACK_P3
//ATTACK_LEFT, ATTACK_RIGHT , ATTACK_LEFT,ATTACK_RIGHT
// data points for single full sinusoidal wave _/-\_/-
//
const uint8_t sinusoid[257] PROGMEM = {
  0, 3, 6, 9, 12, 15, 18, 21, 24, 28, 31, 34, 37, 40, 43, 46, 49, 52,
  55, 58, 61, 64, 68, 71, 74, 77, 79, 82, 85, 88, 91, 94, 97, 100, 103,
  106, 109, 111, 114, 117, 120, 122, 125, 128, 131, 133, 136, 139, 141,
  144, 146, 149, 151, 154, 156, 159, 161, 164, 166, 168, 171, 173, 175,
  178, 180, 182, 184, 186, 188, 191, 193, 195, 197, 199, 201, 202, 204,
  206, 208, 210, 212, 213, 215, 217, 218, 220, 221, 223, 224, 226, 227,
  229, 230, 231, 233, 234, 235, 236, 237, 239, 240, 241, 242, 243, 244,
  244, 245, 246, 247, 248, 248, 249, 250, 250, 251, 251, 252, 252, 253,
  253, 253, 254, 254, 254, 254, 254, 254, 254, 255, 254, 254, 254, 254,
  254, 254, 254, 253, 253, 253, 252, 252, 251, 251, 250, 250, 249, 248,
  248, 247, 246, 245, 244, 244, 243, 242, 241, 240, 239, 237, 236, 235,
  234, 233, 231, 230, 229, 227, 226, 224, 223, 221, 220, 218, 217, 215,
  213, 212, 210, 208, 206, 204, 202, 201, 199, 197, 195, 193, 191, 188,
  186, 184, 182, 180, 178, 175, 173, 171, 168, 166, 164, 161, 159, 156,
  154, 151, 149, 146, 144, 141, 139, 136, 133, 131, 128, 125, 122, 120,
  117, 114, 111, 109, 106, 103, 100, 97, 94, 91, 88, 85, 82, 79, 77,
  74, 71, 68, 64, 61, 58, 55, 52, 49, 46, 43, 40, 37, 34, 31, 28, 24,
  21, 18, 15, 12, 9, 6, 3, 0
};


// data points for color cycling
//
const uint8_t colorCycleData[] PROGMEM = {
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,
    0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,   0,

    0,   2,   4,   6,   8,  10,  12,  14,  16,  18,  20,  22,  24,  26,  28,  30,
   32,  35,  38,  41,  44,  47,  50,  53,  56,  59,  62,  65,  68,  71,  74,  77,
   81,  85,  89,  93,  97, 101, 105, 109, 113, 117, 121, 125, 129, 133, 137, 141,
  148, 155, 162, 169, 176, 183, 190, 197, 204, 211, 218, 225, 232, 239, 246, 253,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,
  255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255,

  253, 246, 239, 232, 225, 218, 211, 204, 197, 190, 183, 176, 169, 162, 155, 148,
  141, 137, 133, 129, 125, 121, 117, 113, 109, 105, 101,  97,  93,  89,  85,  81,
   77,  74,  71,  68,  65,  62,  59,  56,  53,  50,  47,  44,  41,  38,  35,  32,
   30,  28,  26,  24,  22,  20,  18,  16,  14,  12,  10,   8,   6,   4,   2,   0
};



#endif
