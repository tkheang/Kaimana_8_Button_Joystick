//  kaimana.h
//
//  Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
//  All rights reserved.  Use is subject to license terms.
//
//  Code is provided for entertainment purposes and use with the Kaimana controller.
//  Code may be copied, modified, resused with this Copyright notice.
//  No commercial use without written permission from Paradise Arcade Shop.
//
//  Paradise Arcade Shop Kaimana LED Driver Board
//  Initial Release October 15, 2013
//
//  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
//  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
//  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
//  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
//  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
//  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
//  THE SOFTWARE.
//
//  Kaimana class based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//

#ifndef __kaimana_h__
#define __kaimana_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana_custom.h"
#include "settings.h"


// Map function names to arduino leonardo atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  PIN_DOWN    11
#define  PIN_UP      18
#define  PIN_LEFT    19
#define  PIN_RIGHT   20
#define  PIN_HOME    8
#define  PIN_GUIDE   8
#define  PIN_SELECT  9
#define  PIN_BACK    9
#define  PIN_START   10
#define  PIN_P1      3
#define  PIN_P2      2
#define  PIN_P3      0
#define  PIN_P4      1
#define  PIN_K1      4
#define  PIN_K2      21
#define  PIN_K3      12
#define  PIN_K4      6
//
#define  PIN_LED     23


// Map function names to binary input masks on atmega32u4 digital pin numbers
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
#define  ATTACK_UP      0x0800UL
#define  ATTACK_DOWN    0x0400UL
#define  ATTACK_LEFT    0x0200UL
#define  ATTACK_RIGHT   0x0100UL
#define  ATTACK_K4      0x0080UL
#define  ATTACK_K3      0x0040UL
#define  ATTACK_K2      0x0020UL
#define  ATTACK_K1      0x0010UL
#define  ATTACK_P4      0x0008UL
#define  ATTACK_P3      0x0004UL
#define  ATTACK_P2      0x0002UL
#define  ATTACK_P1      0x0001UL
#define  ATTACK_NONE    0x0000UL
#define  ATTACK_FALSE   0xFFFFUL


// number of switch inputs on kaimana
#define  SWITCH_COUNT         15

// if this is changed then Kaimana::switchHistoryTest must also be revised
#define SWITCH_HISTORY_MAX  16


// basic color definitions with various R,G,B values
// generic (may  want to prefix with COLOR_* to localize further)
#define  BLACK    000,000,000
#define  RED      255,000,000
#define  GREEN    000,255,000
#define  YELLOW   255,255,000
#define  BLUE     000,000,255
#define  PURPLE   255,000,255
#define  CYAN     000,255,255
#define  WHITE    255,255,255
#define  MAGENTA  255,000,255
#define  ORANGE   220,127,000
// RGB value structure.
typedef struct __attribute__ ((__packed__)) {
    uint8_t r;
    uint8_t g;
    uint8_t b;
} RGB_t;


// table of switch pin numbers
const unsigned char switchPins[SWITCH_COUNT] = { PIN_DOWN, PIN_UP, PIN_LEFT, PIN_RIGHT, PIN_HOME, PIN_SELECT, PIN_START, PIN_P1, PIN_P2, PIN_P3, PIN_P4, PIN_K1, PIN_K2, PIN_K3, PIN_K4 };


// define the Kaimana class
//
class Kaimana
{
  private:
    // declare RGB array for 15 buttons --> 12 LEDs
    // specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
    RGB_t    _led[LED_COUNT];
    uint16_t _switchHistory[SWITCH_HISTORY_MAX];

  public:
    Kaimana(void);
    void    setLED(int index, int iR, int iG, int iB);
	  void    setLEDBrightness(int index, int iR, int iG, int iB,float alpha=0);
    void    setALL(int iR, int iG, int iB);
    void    updateALL(void);
    void    switchHistoryClear(void);
    void    switchHistorySet(uint16_t latestValue);
    boolean switchHistoryTest( uint16_t a0=ATTACK_FALSE, uint16_t a1=ATTACK_FALSE, uint16_t a2=ATTACK_FALSE,  uint16_t a3=ATTACK_FALSE,  uint16_t a4=ATTACK_FALSE,  uint16_t a5=ATTACK_FALSE,  uint16_t a6=ATTACK_FALSE,  uint16_t a7=ATTACK_FALSE, uint16_t a8=ATTACK_FALSE, uint16_t a9=ATTACK_FALSE, uint16_t a10=ATTACK_FALSE, uint16_t a11=ATTACK_FALSE, uint16_t a12=ATTACK_FALSE, uint16_t a13=ATTACK_FALSE, uint16_t a14=ATTACK_FALSE, uint16_t a15=ATTACK_FALSE );
};


// prototypes for Kaimana functions
// specific to ParadiseArcadeShop.com Kaimana board (PS360+LED)
void 	setLED(int index, int iR, int iG, int iB);
void 	setALL(int iR, int iG, int iB);
void 	updateALL(void);
void 	switchHistoryClear(void);
void 	switchHistorySet(uint16_t latestValue);
boolean switchHistoryTest( uint16_t a0=ATTACK_FALSE, uint16_t a1=ATTACK_FALSE, uint16_t a2=ATTACK_FALSE,  uint16_t a3=ATTACK_FALSE,  uint16_t a4=ATTACK_FALSE,  uint16_t a5=ATTACK_FALSE,  uint16_t a6=ATTACK_FALSE,  uint16_t a7=ATTACK_FALSE, uint16_t a8=ATTACK_FALSE, uint16_t a9=ATTACK_FALSE, uint16_t a10=ATTACK_FALSE, uint16_t a11=ATTACK_FALSE, uint16_t a12=ATTACK_FALSE, uint16_t a13=ATTACK_FALSE, uint16_t a14=ATTACK_FALSE, uint16_t a15=ATTACK_FALSE );


#endif
