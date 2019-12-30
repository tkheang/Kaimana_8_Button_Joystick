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
// Revised: April  11, 2015 zonbipanda // gmail.com -- Arduino 1.6.3 Support
// Revised: March 7, 2016  info // mightyjrmods.com -- Added startup animations
// Revised: December 6, 2019 tkheang -- Custom Etokki Omni configuration w/ 12-LED ring
//

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
int tourneypollSwitches(void);
boolean tournamentMode = false;
int holdTimeout = 0;
int selection = 0;
int intensity=0;
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
    static int iLED[LED_COUNT];
    static int iActiveSwitchCount;
    static int i;
    static int j;
    static int firsttime;
    static uint16_t joystickDirection;
    static uint16_t switchActivity;
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
            //setLEDRandomColor(LED_JOY_R);
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, CYAN);
            kaimana.setLED(LED_JOY_U, BLACK);
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = true;
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = false;
            break;
        case ATTACK_LEFT: // left
            //setLEDRandomColor(LED_JOY_L);
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, CYAN);
            kaimana.setLED(LED_JOY_R, BLACK);
            kaimana.setLED(LED_JOY_U, BLACK);
            iLED[LED_JOY_L] = true;
            iLED[LED_JOY_R] = false;
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = false;
            break;
        case ATTACK_DOWN: // down
            //setLEDRandomColor(LED_JOY_D);
            kaimana.setLED(LED_JOY_D, CYAN);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, BLACK);
            kaimana.setLED(LED_JOY_U, BLACK);
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = false;
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = true;
            break;
        case ATTACK_DOWN + ATTACK_RIGHT: // down + right
            kaimana.setLED(LED_JOY_D, CYAN);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, CYAN);
            kaimana.setLED(LED_JOY_U, BLACK);
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = true;
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = true;
            break;
        case ATTACK_DOWN + ATTACK_LEFT: // down + left
            kaimana.setLED(LED_JOY_D, CYAN);
            kaimana.setLED(LED_JOY_L, CYAN);
            kaimana.setLED(LED_JOY_R, BLACK);
            kaimana.setLED(LED_JOY_U, BLACK);
            iLED[LED_JOY_L] = true;
            iLED[LED_JOY_R] = false;
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = true;
            break;
        case ATTACK_UP: // up
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, BLACK);
            kaimana.setLED(LED_JOY_U, CYAN);
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = false;
            iLED[LED_JOY_U] = true;
            iLED[LED_JOY_D] = false;
            break;
        case ATTACK_UP + ATTACK_RIGHT: // up + right
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, CYAN);
            kaimana.setLED(LED_JOY_U, CYAN);
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = true;
            iLED[LED_JOY_U] = true;
            iLED[LED_JOY_D] = false;
            break;
        case ATTACK_UP + ATTACK_LEFT:  // up + left
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, CYAN);
            kaimana.setLED(LED_JOY_R, BLACK);
            kaimana.setLED(LED_JOY_U, CYAN);
            iLED[LED_JOY_L] = true;
            iLED[LED_JOY_R] = false;
            iLED[LED_JOY_U] = true;
            iLED[LED_JOY_D] = false;
            break;
        default:  // zero or any undefined value on an 8 way stick like UP+DOWN which is not happening on my watch
            kaimana.setLED(LED_JOY_U, BLACK);
            kaimana.setLED(LED_JOY_D, BLACK);
            kaimana.setLED(LED_JOY_L, BLACK);
            kaimana.setLED(LED_JOY_R, BLACK);
            iLED[LED_JOY_U] = false;
            iLED[LED_JOY_D] = false;
            iLED[LED_JOY_L] = false;
            iLED[LED_JOY_R] = false;
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
    // test switch and set LED based on result
    if(!digitalRead(PIN_P1)) {
        switchActivity |= ATTACK_P1;
        // switch is active
        if(iLED[LED_P1] == true) {
            //maintain color while switch is active
            iLED[LED_P1] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_P1);
            iLED[LED_P1] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_P1, BLACK);
        iLED[LED_P1] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_P2)) {
        switchActivity |= ATTACK_P2;
        // switch is active
        if(iLED[LED_P2] == true) {
            //maintain color while switch is active
            iLED[LED_P2] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_P2);
            iLED[LED_P2] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_P2, BLACK);
        iLED[LED_P2] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_P3)) {
        switchActivity |= ATTACK_P3;
        // switch is active
        if(iLED[LED_P3] == true) {
            //maintain color while switch is active
            iLED[LED_P3] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_P3);
            iLED[LED_P3] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_P3, BLACK);
        iLED[LED_P3] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_P4)) {
        switchActivity |= ATTACK_P4;
        // switch is active
        if(iLED[LED_P4] == true) {
            //maintain color while switch is active
            iLED[LED_P4] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_P4);
            iLED[LED_P4] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_P4, BLACK);
        iLED[LED_P4] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_K1)) {
        switchActivity |= ATTACK_K1;
        // switch is active
        if(iLED[LED_K1] == true) {
            //maintain color while switch is active
            iLED[LED_K1] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_K1);
            iLED[LED_K1] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_K1, BLACK);
        iLED[LED_K1] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_K2)) {
        switchActivity |= ATTACK_K2;
        // switch is active
        if(iLED[LED_K2] == true) {
            //maintain color while switch is active
            iLED[LED_K2] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_K2);
            iLED[LED_K2] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_K2, BLACK);
        iLED[LED_K2] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_K3)) {
        switchActivity |= ATTACK_K3;
        // switch is active
        if(iLED[LED_K3] == true) {
            //maintain color while switch is active
            iLED[LED_K3] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_K3);
            iLED[LED_K3] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_K3, BLACK);
        iLED[LED_K3] = false;
    }
    // test switch and set LED based on result
    if(!digitalRead(PIN_K4)) {
        switchActivity |= ATTACK_K4;
        // switch is active
        if(iLED[LED_K4] == true) {
            //maintain color while switch is active
            iLED[LED_K4] = true;
        }
        else {
            // select new color when switch is first activated
            setLEDRandomColor(LED_K4);
            iLED[LED_K4] = true;
        }
    }
    else {
        // switch is inactive
        kaimana.setLED(LED_K4, BLACK);
        iLED[LED_K4] = false;
    }
    
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
    
    // zero active switch counter (note: 4 way joystick counts as 1)
    iActiveSwitchCount = 0;
    // set LED color based on switch
    for(i=0;i<LED_COUNT;++i) {
        if(iLED[i] == true)
        ++iActiveSwitchCount;
    }

    // turn off touchpad LED
    kaimana.setLED(LED_TP, BLACK);
    
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
    if(!digitalRead(PIN_HOME)) {
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
