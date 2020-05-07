// Copyright 2013 Paradise Arcade Shop, ParadiseArcadeShop.com
// All rights reserved. Use is subject to license terms.
//
// Code is provided for entertainment purposes and use with the Kaimana controller.
// Code may be copied, modified, resused with this Copyright notice.
// No commercial use without written permission from Paradise Arcade Shop.
//
// Paradise Arcade Shop Kaimana LED Driver Board
// Initial Release October 15, 2013
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
// THE SOFTWARE.
//
// Kaimana example based on original source released by ParadiseArcadeShop.com October 15, 2013
//
// Created: October 24, 2013 zonbipanda // gmail.com -- Arduino 1.0.5 Support
// Revised: October 29, 2013 zonbipanda // gmail.com
// Revised: April   11, 2015 zonbipanda // gmail.com -- Arduino 1.6.3 Support
// Revised: March    7, 2016 info // mightyjrmods.com -- Added startup animations
// Revised: May      6, 2020 tkheang  -- Removed unused animations

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <util/delay.h>
#include "kaimana.h"
#include "kaimana_custom.h"
#include "animations.h"
#include "settings.h"

// local function declarations
int pollSwitches(void);
void showStartup(void);
void setLEDRandomColor(int index);
void readAttackSwitch(int pin, int attack, int LED);
void setJOYLEDRandomColor(int dir);
int tourneypollSwitches(void);

boolean tournamentMode = false;
int holdTimeout = 0;
int selection = 0;
int intensity=0;

// moved these variables outside the pollSwitches function
static int iLED[LED_COUNT];
static uint16_t switchActivity;

// ParadiseArcadeShop.com Kaimana features initialzied when Kaimana class instantiated
Kaimana kaimana;

// the setup routine runs first and once each time power is applied to the Kaimana board
void setup()
{
    // light up all leds at boot to demonstrate everything is functional
    _STARTUP_ANIMATION
}

// the loop routine repeats indefinitely and executes immediately following the setup() function
void loop() {
    unsigned long ulTimeout;
    // initialize timeout value to now + some seconds
    ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
    // infinite loop of read switches, update LEDs and idle animation when necessary
    while( true) {
        // active -- poll switches and update leds
        if (tournamentMode != true) {
            if( pollSwitches() != 0 ) {
                // some switches were active so reset idle timeout to now + some seconds
                ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
            }
            else {
                // no switches active so test for start of idle timeout
                if( millis() > ulTimeout ) {
                    animation_idle();
                }
            }
        }
        else {
            if( tourneypollSwitches() != 0 ) {
                // some switches were active so reset idle timeout to now + some seconds
                ulTimeout = millis() + ( (unsigned long)IDLE_TIMEOUT_SECONDS * 1000 );
            }
        }
    }
}

// ==============================================================
//
// local functions start here
//
// ==============================================================
int pollSwitches(void) {
    // static int iLED[LED_COUNT];
    static int iActiveSwitchCount;
    static int i;
    static int j;
    static int firsttime;
    static uint16_t joystickDirection;
    // static uint16_t switchActivity;
    // reset LED status
    if (firsttime == 1) {
        for(i=0;i<LED_COUNT;++i) {
            iLED[i] = false;
            firsttime = 0;
        }
    }
    
    // read arduino pins and save results in the mapped LED if button is pressed (pin grounded)
        
    // complex special case for joystick but it's worth the effort
    joystickDirection = ATTACK_NONE;
    if(!digitalRead(PIN_RIGHT))
    joystickDirection |= ATTACK_RIGHT;
    if(!digitalRead(PIN_LEFT))
    joystickDirection |= ATTACK_LEFT;
    if(!digitalRead(PIN_DOWN))
    joystickDirection |= ATTACK_DOWN;
    if(!digitalRead(PIN_UP))
    joystickDirection |= ATTACK_UP;

    switch(joystickDirection) {
        case ATTACK_RIGHT: // right
            setJOYLEDRandomColor(PIN_RIGHT);
            break;
        case ATTACK_LEFT: // left
            setJOYLEDRandomColor(PIN_LEFT);
            break;
        case ATTACK_DOWN: // down
            setJOYLEDRandomColor(PIN_DOWN);
            break;
        case ATTACK_DOWN + ATTACK_RIGHT: // down + right
            setJOYLEDRandomColor(PIN_DOWN);
            setJOYLEDRandomColor(PIN_RIGHT);
            break;
        case ATTACK_DOWN + ATTACK_LEFT: // down + left
            setJOYLEDRandomColor(PIN_DOWN);
            setJOYLEDRandomColor(PIN_LEFT);
            break;
        case ATTACK_UP: // up
            setJOYLEDRandomColor(PIN_UP);
            break;
        case ATTACK_UP + ATTACK_RIGHT: // up + right
            setJOYLEDRandomColor(PIN_UP);
            setJOYLEDRandomColor(PIN_RIGHT);
            break;
        case ATTACK_UP + ATTACK_LEFT:  // up + left
            setJOYLEDRandomColor(PIN_UP);
            setJOYLEDRandomColor(PIN_LEFT);
            break;
        default:  // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
            kaimana.setLED(28, BLACK);
            iLED[28] = false;
            kaimana.setLED(29, BLACK);
            iLED[29] = false;
            kaimana.setLED(30, BLACK);
            iLED[30] = false;
            kaimana.setLED(31, BLACK);
            iLED[31] = false;
            kaimana.setLED(32, BLACK);
            iLED[32] = false;
            kaimana.setLED(33, BLACK);
            iLED[33] = false;
            kaimana.setLED(34, BLACK);
            iLED[34] = false;
            kaimana.setLED(35, BLACK);
            iLED[35] = false;
            kaimana.setLED(36, BLACK);
            iLED[36] = false;
            kaimana.setLED(37, BLACK);
            iLED[37] = false;
            kaimana.setLED(38, BLACK);
            iLED[38] = false;
            kaimana.setLED(39, BLACK);
            iLED[39] = false;
            break;
    }
    
    // clear results for switch activity
    switchActivity = ATTACK_NONE;
    
    // test switch and set LED based on result  // HOME = GUIDE
    if(!digitalRead(PIN_HOME)) {
        // switch is active
        if(iLED[LED_HOME] == true) {
            //maintain color while switch is active
            iLED[LED_HOME] = true;
            holdTimeout += 1;
            //Button hold to start tourneymode
            if(holdTimeout == 2000) {
                tournamentMode = true;
                tourneyModeActivate();
            }
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_HOME);
            iLED[LED_HOME] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_HOME, BLACK);
        iLED[LED_HOME] = false;
        holdTimeout=0;
    }
    
    // test switch and set LED based on result // SELECT = BACK
    if(!digitalRead(PIN_SELECT)) {
        // switch is active
        if(iLED[LED_SELECT] == true)
        {
            //maintain color while switch is active
            iLED[LED_SELECT] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_SELECT);
            iLED[LED_SELECT] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_SELECT, BLACK);
        iLED[LED_SELECT] = false;
    }
    
    // test switch and set LED based on result
    if(!digitalRead(PIN_START)) {
        // switch is active
        if(iLED[LED_START] == true) {
            //maintain color while switch is active
            iLED[LED_START] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_START);
            iLED[LED_START] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_START, BLACK);
        iLED[LED_START] = false;
    }

    // test attack switches and set LED based on result
    readAttackSwitch(PIN_P1, ATTACK_P1, LED_P1);
    readAttackSwitch(PIN_P2, ATTACK_P2, LED_P2);
    readAttackSwitch(PIN_P3, ATTACK_P3, LED_P3);
    readAttackSwitch(PIN_P4, ATTACK_P4, LED_P4);
    readAttackSwitch(PIN_K1, ATTACK_K1, LED_K1);
    readAttackSwitch(PIN_K2, ATTACK_K2, LED_K2);
    readAttackSwitch(PIN_K3, ATTACK_K3, LED_K3);
    readAttackSwitch(PIN_K4, ATTACK_K4, LED_K4);
    
    // convert joystick, P1-P4, K1-K4 into a single unsigned int
    switchActivity = joystickDirection + switchActivity;
    kaimana.switchHistorySet(switchActivity);
    // test for combinations from most complext to least complex
    // test for switches in reverse order (newest to oldest)
    // combo #6
    // test for: Ultra 2 (Metsu Shoryuken)
    // combo is: DOWN, DOWN+RIGHT, RIGHT, DOWN, DOWN+RIGHT, RIGHT, RIGHT+K3
    if( kaimana.switchHistoryTest( COMBO_PATTERN_6A ) )
    animation_combo_6();
    // combo #5
    // test for: Ultra 1 (Metsu Hadouken)
    // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P3
    if( kaimana.switchHistoryTest( COMBO_PATTERN_5A ) )
    animation_combo_5();
    // combo #4
    // test for: Super (Shinkuu Hadouken)
    // combo is: DOWN, DOWN+RIGHT, RIGHT, <NONE>, DOWN, DOWN+RIGHT, RIGHT, RIGHT+P1
    if( kaimana.switchHistoryTest( COMBO_PATTERN_4A ) )
    animation_combo_4();
    // combo #3
    // test for: 214 + K or 236 + K
    if(kaimana.switchHistoryTest(COMBO_PATTERN_3A) || kaimana.switchHistoryTest(COMBO_PATTERN_3B) || kaimana.switchHistoryTest(COMBO_PATTERN_3C) || kaimana.switchHistoryTest(COMBO_PATTERN_3D) || kaimana.switchHistoryTest(COMBO_PATTERN_3E) || kaimana.switchHistoryTest(COMBO_PATTERN_3F))
    animation_combo_3();
    // combo #2
    // test for: 623 + P or 421 + P
    if(kaimana.switchHistoryTest(COMBO_PATTERN_2A) || kaimana.switchHistoryTest(COMBO_PATTERN_2B) || kaimana.switchHistoryTest(COMBO_PATTERN_2C) || kaimana.switchHistoryTest(COMBO_PATTERN_2D) || kaimana.switchHistoryTest(COMBO_PATTERN_2E) || kaimana.switchHistoryTest(COMBO_PATTERN_2F))
    animation_combo_2();
    // combo #1
    // test for: 236 + P or 214 + P
    if(kaimana.switchHistoryTest(COMBO_PATTERN_1A) || kaimana.switchHistoryTest(COMBO_PATTERN_1B) || kaimana.switchHistoryTest(COMBO_PATTERN_1C))
    animation_combo_1A();
    if(kaimana.switchHistoryTest(COMBO_PATTERN_1D) || kaimana.switchHistoryTest(COMBO_PATTERN_1E) || kaimana.switchHistoryTest(COMBO_PATTERN_1F))
    animation_combo_1B();
    
    // zero active switch counter
    iActiveSwitchCount = 0;
    // set LED color based on switch
    for (i = 0; i < LED_COUNT; ++i) {
        if(iLED[i] == true)
          ++iActiveSwitchCount;
    }

    // turn off touchpad, R3, and L3 LEDs
    kaimana.setLED(LED_TP, BLACK);
    kaimana.setLED(LED_R3, BLACK);
    kaimana.setLED(LED_R3_B, BLACK);
    kaimana.setLED(LED_L3, BLACK);
    kaimana.setLED(LED_L3_B, BLACK);
    
    // update the leds with new/current colors in the array
    kaimana.updateALL();
    // return number of active switches
    return(iActiveSwitchCount);
}

int tourneypollSwitches(void) {
    static int iLED[LED_COUNT];
    static int iActiveSwitchCount = 0;
    static int i;
    static int j;
    static int firsttime;
    static uint16_t joystickDirection;
    static uint16_t switchActivity;
    // test switch and set LED based on result  // HOME = GUIDE
    if (!digitalRead(PIN_HOME)) {
        //Button hold to change idle animation
        holdTimeout += 1;
        //Button hold to start tourneymode
        if(holdTimeout == 200)
        {
            tournamentMode = false;
            tourneyModeDeactivate();
        }
        ++iActiveSwitchCount;
        delay(10);
    }
    else {
        holdTimeout=0;
    }
    return(iActiveSwitchCount);
}

void readAttackSwitch(int pin, int attack, int LED) {
  if (!digitalRead(pin)) {
        switchActivity |= attack;
        // switch is active
        if(iLED[LED] == true) {
            //maintain color while switch is active
            iLED[LED] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED);
            iLED[LED] = true;
        }
    }
  else {
        // switch is inactive
        kaimana.setLED(LED, BLACK);
        iLED[LED] = false;
    }
}

// There's definitely a better way to implement this lmao
void setJOYLEDRandomColor(int dir) {
  int i;
  if (!digitalRead(dir)) {
      // switch is active
      if(iLED[LED_J1] == true) {
          //maintain color while switch is active
          iLED[LED_J1] = true;
      }
      else {
        switch(random(1, 8)) {
          case 1:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_1); 
              }
              iLED[LED_J1] = true;
            break;
          case 2:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_2); 
              }
              iLED[LED_J1] = true;
            break;
          case 3:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_3); 
              }
              iLED[LED_J1] = true;
            break;
          case 4:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_4); 
              }
              iLED[LED_J1] = true;
            break;
          case 5:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_5); 
              }
              iLED[LED_J1] = true;
            break;
          case 6:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_6); 
              }
              iLED[LED_J1] = true;
            break;
          case 7:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_7); 
              }
              iLED[LED_J1] = true;
            break;
          case 8:
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, COLOR_RANDOM_8); 
              }
              iLED[LED_J1] = true;
            break;
          default:  // any undefined value so discard data and set led to BLACK
            for (i = 28; i < 40; i++) {
                kaimana.setLED(i, BLACK); 
              }
              iLED[LED_J1] = true;
            break;
      }
    }
  }
  else {
      // switch is inactive
      kaimana.setLED(28, BLACK);
      kaimana.setLED(29, BLACK);
      kaimana.setLED(30, BLACK);
      kaimana.setLED(31, BLACK);
      kaimana.setLED(32, BLACK);
      kaimana.setLED(33, BLACK);
      kaimana.setLED(34, BLACK);
      kaimana.setLED(35, BLACK);
      kaimana.setLED(36, BLACK);
      kaimana.setLED(37, BLACK);
      kaimana.setLED(38, BLACK);
      kaimana.setLED(39, BLACK);
      iLED[LED_J1] = false;
  }
}
