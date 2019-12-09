//Change settings here instead of in the other library files.

/*
THIS ONE DOESNT WORK YET JUST LEAVE IT AT THE DEFAULT
##LED ORDER OPTIONS## 
Select how many LEDS are in your setup from the list, or leave at _LED_ORDER_FULL for the default 23 LEDS
_LED_ORDER_FULL
_LED_ORDER_NO_MENU
_LED_ORDER_NO_MENU_NO_JOY
*/

#define  _LED_ORDER_FULL

/*
##LED BRIGHTNESS##
Set your brightness to a value between 0 and 1 (example 0.5 is half bright)
*/

#define _LED_BRIGHTNESS 0.5

/*
##IDLE COLOR##
Set your IDLE color here, this will affect ALL animations that have a single color, you can select from the list or define your own value in the format RRR,GGG,BBB (example 255,255,255 is white)
BLACK  (buttons are OFF)
RED    
GREEN  
YELLOW 
BLUE   
PURPLE 
CYAN   
WHITE  
MAGENTA
ORANGE 
*/

#define _IDLE_COLOR GREEN

/*
##ON PRESS BUTTON COLOR##
Set button color on press, same color options as above. 
Add a // to the beginning of the _COLOR_RANDOM line to use the color on press.

select BLACK to have them remain off.
*/
#define _COLOR_RANDOM
//#define _ON_PRESS_BTN_COLOR GREEN

/*
##START UP ANIMATION##
Define which startup animation should play from the list, or leave at START_DEFAULT_ANIMATION for the default one.
_START_DEFAULT_ANIMATION
_START_WALK_ANIMATION
_START_STAR_ANIMATION
*/

#define _STARTUP_ANIMATION _START_DEFAULT_ANIMATION

/*
##IDLE ANIMATION##
You can select an individual animation here from the list, or leave at _IDLE_DEFAULT for the deafaule animation, remove the // from _IDLE_ALL to be able to cycle through the animations using the HOMe button
_IDLE_ALL
_IDLE_DEFAULT
_IDLE_WALK_ANIMATION
_IDLE_STAR_ANIMATION
_IDLE_BREATHE_ANIMATION
_IDLE_BREATHE_MAC_ANIMATION
*/

//#define _IDLE_ALL true
//#define _IDLE_ANIMATION _IDLE_WALK_ANIMATION
