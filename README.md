# Kaimana LED Code for 14-Button Fightstick with RGB LED Ring
Code for Paradise Arcade Shop's Kaimana Mini installed in my AllFightSticks fightstick. Modified from original code found [here](https://github.com/javierorosario/kaimana).  

# Hardware
[Kaimana RGB LEDs, driver PCB, and wiring from Paradise Arcade Shop](https://paradisearcadeshop.com/home/electrical/pcbs-lighting/led-lighting-solutions/436-paradise-arcade-kaimana-led-series)  
[NeoPixel Ring - 12 x 5050 RGB LED from Adafruit](https://www.adafruit.com/product/1643)  
Note that this NeoPixel ring only has standard RGB LEDs and no separate white LEDs. This will make it easier to integrate with the Kaimana Mini. 

# Overview
I'm using 12 Kaimana J2 LEDs and 1 12-LED NeoPixel ring (used for the joystick) in this order: K4-K3-K2-K1-P4-P3-P2-P1-START-SELECT-HOME-TOUCHPAD-R3-L3-JOYSTICK.  
The code structure and functions are explained on the [MightyJRMods website](http://www.mightyjrmods.com/kaimana-guide).  
