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
void readJoystickSwitch();
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
    // Serial.begin(9600);
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
                    // animation_idle();
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
    if(!digitalRead(PIN_RIGHT)) {
      joystickDirection |= ATTACK_RIGHT;
    }
    if(!digitalRead(PIN_LEFT)) {
      joystickDirection |= ATTACK_LEFT;
    }
    if(!digitalRead(PIN_DOWN)) {
      joystickDirection |= ATTACK_DOWN;
    }
    if(!digitalRead(PIN_UP)) {
      joystickDirection |= ATTACK_UP;
    }

    switch(joystickDirection) {
        case ATTACK_RIGHT: // right
            readJoystickSwitch();
            break;
        case ATTACK_LEFT: // left
            readJoystickSwitch();
            break;
        case ATTACK_DOWN: // down
            readJoystickSwitch();
            break;
        case ATTACK_DOWN + ATTACK_RIGHT: // down + right
            readJoystickSwitch();
            break;
        case ATTACK_DOWN + ATTACK_LEFT: // down + left
            readJoystickSwitch();
            break;
        case ATTACK_UP: // up
            readJoystickSwitch();
            break;
        case ATTACK_UP + ATTACK_RIGHT: // up + right
            readJoystickSwitch();
            break;
        case ATTACK_UP + ATTACK_LEFT:  // up + left
            readJoystickSwitch();
            break;
        default:  // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
            kaimana.setLED(LED_JOY, BLACK);
            iLED[LED_JOY] = false;
            break;
    }
    
    // clear results for switch activity
    switchActivity = ATTACK_NONE;

    // Enable tourney mode
    if(!digitalRead(PIN_P1) && !digitalRead(PIN_K1) && !digitalRead(PIN_P4) && !digitalRead(PIN_K4)) {
        holdTimeout += 1;
        //Buttons hold to start tourneymode
        if(holdTimeout == 2000) {
            tournamentMode = true;
            tourneyModeActivate();
            holdTimeout = 0;
        }
    }
    else {
        // switches are inactive
        holdTimeout=0;
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
    // KBD
    if(kaimana.switchHistoryTest(KBD_1P) || kaimana.switchHistoryTest(KBD_2P))
    KBD();
    // Wavedash
    if(kaimana.switchHistoryTest(WAVEDASH_1P) || kaimana.switchHistoryTest(WAVEDASH_2P))
    Wavedash();
    
    // zero active switch counter
    iActiveSwitchCount = 0;
    // set LED color based on switch
    for (i = 0; i < LED_COUNT; ++i) {
        if(iLED[i] == true)
          ++iActiveSwitchCount;
    }
    
    // update the leds with new/current colors in the array
    kaimana.updateALL();
    // return number of active switches
    // Serial.println(iActiveSwitchCount);
    return(iActiveSwitchCount);
}

int tourneypollSwitches(void) {
    static int iActiveSwitchCount = 0;
    // test switch and set LED based on result  // HOME = GUIDE
    if (!digitalRead(PIN_P1) && !digitalRead(PIN_K1) && !digitalRead(PIN_P4) && !digitalRead(PIN_K4)) {
        //Button hold to change idle animation
        holdTimeout += 1;
        if(holdTimeout == 2000)
        {
            tournamentMode = false;
            tourneyModeDeactivate();
        }
        ++iActiveSwitchCount;
        delay(10);
    }
    else {
        holdTimeout = 0;
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
            // Light button LED
            // setLEDRandomColor(LED);
            kaimana.setLED(LED, BLUE);
            iLED[LED] = true;
        }
    }
  else {
        // switch is inactive
        kaimana.setLED(LED, BLACK);
        iLED[LED] = false;
    }
}

void readJoystickSwitch() {
  if(iLED[LED_JOY] == true) {
      //maintain color while switch is active
      iLED[LED_JOY] = true;
  }
  else {
      // Light joystick LED
      // setLEDRandomColor(LED_JOY);
      kaimana.setLED(LED_JOY, BLUE);
      iLED[LED_JOY] = true;
  }
}
