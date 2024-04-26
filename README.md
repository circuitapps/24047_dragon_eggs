# 24047 - ATTINY85 DRAGON EGGS LAMP WITH FILAMENT LEDS
---

In this project we are introducing a simple circuit and code that will allow you to create a fully programmable and customizable night lamp with Dragon Eggs theme! We are also leveraging the mighty power of the ATtiny85 microcontroller.

Following is the circuit diagram of the lamp. It is a very simple circuit indeed!

![Dragon eggs lamp circuit](./AtTiny85_dragoneggslamp_24047.png)

You can access the AtTiny85 software code using the following link. This is a great starting point to create your own LED patterns for the earring!

![AtTiny85 code folder](./attiny85_code_24047)

Though the above code showcases the functionality in our **<u>[project video][1]</u>**, there are many other things you can do by introducing simple modifications to this basic code.

Description: This code is designed to support the LED circuit in the Dragon Eggs LED Lamp project. Following two core lighting effects can be enabled in this code simply by commenting in one of the following lines:

//#define FADER_EFFECT

//#define SPARKLE_EFFECT
  
The LED on and off timings are randomized through the use of EEPROM content for sroting and updating seed after each power up. Therefore, the LED patterns do not repeat themselves after each power up. Feel free to modify the following parameters to create new animations:

When #define FADER_EFFECT is commented in:

#define LED_EFFECT_WAIT_TIME <enter time in milliseconds here> Random delay time between two successive Fade in and out pairs.

In led_fader() function, change pwm_levels[] = {}; content to vary the intensity of the fading LEDs

When #define SPARKLE_EFFECT is commented in:

Inside random_sparkles() function:

on_time_ms = random(<change low ms limit>, <change high ms limit>);  // Random LED ON duration picked between 10 ms and 30 ms

off_time_ms = random(<change low ms limit>, <change high ms limit>);  // Random LED OFF duration picked between 500 ms and 1500 ms

If you want to go a step further than just modifying the parameters above, feel free to write your own functions by checking the led_fader() and random_sparkles() functions.

If you build this project, please share your thoughts and suggestions with the rest of circuitapps community in the comments section of **<u>[our YouTube video][1]</u>**. Also, please feel free to talk about any interesting modifications you make and your experimentations!

## Project Challenges
1 - Though this is a simple project, be careful with the polarity of the LEDs when soldering them to the rest of the circuit.

2 - Be sure to clearly mark the LED polarity on the eggs and the headers on the branches to connect them correctly. This will be important if you decide to swap the eggs between different branches or create multiple eggs with different hot glue patterns for swapping.

3 - You can get the filament LEDs using **<u>[this link][3]</u>** As these LEDs have ceramic inside them, they are pretty fragile and can crack easily. Therefore, be ccareful while handling them!

## Useful tip

If you have not worked with ATtiny85 before and need support with the basic operation and programming of this device, have a look at this **<u>[excellent reference][2]</u>** that walks you through the entire process step by step. If you get stuck, drop us a message in the comments section of **<u>[our YouTube video][1]</u>**


GOOD LUCK & ENJOY THE PROGRAMMABLE DRAGON EGG NIGHT LAMP FOR YOURSELF OR AS A GIFT FOR YOUR LOVED ONES !


[1]: INCLUDE YOUTUBE LINK TO VIDEO HERE

[2]: https://circuitdigest.com/microcontroller-projects/programming-attiny85-microcontroller-ic-using-arduin

[3]: https://www.amazon.com/gp/product/B0CL3XH6XY