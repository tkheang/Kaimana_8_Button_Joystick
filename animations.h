//  combo_animatinos.h
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
//  Kaimana animations based on original source released by ParadiseArcadeShop.com October 15, 2013
//
//  Created:  October 24, 2013    zonbipanda // gmail.com  -- Arduino 1.0.5 Support
//  Revised:  October 29, 2013    zonbipanda // gmail.com
//  Revised:  April   11, 2015    zonbipanda // gmail.com  -- Arduino 1.6.3 Support
//  Revised:  May      6, 2020    tkheang  -- Removed unused animations

#ifndef __animations_h__
#define __animations_h__

#define __PROG_TYPES_COMPAT__
#include <avr/io.h>
#include <avr/pgmspace.h>
#include "Arduino.h"
#include "kaimana.h"
#include "kaimana_custom.h"
#include "settings.h"

extern Kaimana kaimana;

#define IDLE_SIZE           768    // size of animation array
#define IDLE_OFFSET_2       512    // used to create animation -- see code
#define IDLE_OFFSET_1       256    // used to create animation -- see code
#define IDLE_OFFSET_0         0    // used to create animation -- see code
#define IDLE_OFFSET          12    // used to create animation -- see code

#define FIREBALL_SIZE       768    // size of animation array
#define FIREBALL_OFFSET_3   288    // used to create animation -- see code
#define FIREBALL_OFFSET_2   192    // used to create animation -- see code
#define FIREBALL_OFFSET_1    96    // used to create animation -- see code
#define FIREBALL_DELAY      350    // value in microseconds

// Special input animations (assumming player 1 side)\
// Based on Street Fighter's default 6-button layout
void animation_combo_1A(void);   // 236 + P
void animation_combo_1B(void);   // 214 + P
void animation_combo_2(void);    // 623 + P or 421 + P
void animation_combo_3(void);    // 214 + K or 236 + K
void animation_combo_4(void);    // Super — Shinkuu Hadouken
void animation_combo_5(void);    // Ultra 1 — Metsu Hadouken
void animation_combo_6(void);    // Ultra 2 — Metsu Hadouken

// other function prototypes
int animation_idle(void);
void defaultStartup(void);
void tourneyModeActivate(void);
void tourneyModeDeactivate(void);
void KBD(void);
void Wavedash(void);

#endif
