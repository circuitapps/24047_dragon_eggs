
/*
  Dragon eggs LED Lamp

  Operation: This code is designed to support the LED circuit in the Dragon Eggs LED Lamp project. Following two core lighting effects can be enabled in this code simply by commenting in one of the following lines:

  //#define FADER_EFFECT
  //#define SPARKLE_EFFECT
  
  The LED on and off timings are randomized through the use of EEPROM content for sroting and updating seed after each power up. Therefore, the LED patterns do not repeat themselves after each power up. Feel free to modify
  the following parameters to create new animations:

  When #define FADER_EFFECT is commented in:
  #define LED_EFFECT_WAIT_TIME <enter time in milliseconds here> Random delay time between two successive Fade in and out pairs.
  In led_fader() function, change pwm_levels[] = {}; content to vary the intensity of the fading LEDs

  When #define SPARKLE_EFFECT is commented in:
  Inside random_sparkles() function:
  on_time_ms = random(<change low ms limit>, <change high ms limit>);  // Random LED ON duration picked between 10 ms and 30 ms
  off_time_ms = random(<change low ms limit>, <change high ms limit>);  // Random LED OFF duration picked between 500 ms and 1500 ms

  If you want to go a step further than just modifying the parameters above, feel free to write your own functions by checking the led_fader() and random_sparkles() functions.

  Good luck & enjoy!

  by circuitapps
  April 2024
*/
#include <avr/io.h>
#include <EEPROM.h>

//#define FADER_EFFECT
#define SPARKLE_EFFECT

// PORT B DEFINITIONS
#define PB5_PIN1 PB5
#define PB4_PIN3 PB4
#define PB3_PIN2 PB3
#define PB2_PIN7 PB2
#define PB1_PIN6 PB1
#define PB0_PIN5 PB0

#define RANDOM_SEED_EEPROM_ADDRESS 0  // This is where the random number generator seed will be stored on EEPROM

// Application pin definitions
#define FADING_OUT PB1_PIN6

#define LED_EFFECT_WAIT_TIME 120  // Every LED_EFFECT_WAIT_TIME ms a new LED light intensity will be observed
#define PWM_LOWEST_LEVEL 3  // Experimentally identified

#define FADE_OUT 0
#define FADE_IN 1

#define PWM_REGISTER OCR1A  // This is where the high duration (out of a max of 255) needs to be written

void timer_counter_1_pwm_setup()
{
  TCCR1 = 1<<PWM1A | 1<<COM1A0 | 1<<CS10;
  // OC1A is the output to pin 6 of Attiny85 (as per datasheet)
}

void random_seed_manager()
{
  // This function is meant to keep seeds different between powercycles/resets of the MCU
  int seed = EEPROM.read(RANDOM_SEED_EEPROM_ADDRESS);
  randomSeed(seed);
  seed = (seed + 1) & 0xFF;  // seed is a single byte
  EEPROM.update(RANDOM_SEED_EEPROM_ADDRESS, seed);  // Update random seed for next power cycle
  delay(100);  // wait for write to complete
}

void enable_LED(unsigned int pin_name)
{
  digitalWrite(pin_name, HIGH);
}

void disable_LED(unsigned int pin_name)
{
  digitalWrite(pin_name, LOW);
}

void wait_ms(unsigned int delay_ms)
{
  delay(delay_ms);
}

void random_sparkles()
{
  int on_time_ms, off_time_ms;

    on_time_ms = random(10, 30);  // Random LED ON duration picked between 10 ms and 30 ms
    off_time_ms = random(500, 1500);  // Random LED OFF duration picked between 500 ms and 1500 ms

    enable_LED(FADING_OUT);
    wait_ms(on_time_ms);  // keep LED on for a while
    disable_LED(FADING_OUT);
    wait_ms(off_time_ms);  // keep LED off for a while
}

void led_fader()
{
  unsigned int count_state = FADE_IN;  // start with fade in effect
  //  Any maximum pwm_levels[] element can be 255. This determines the LED intensity level.
  unsigned int pwm_levels[] = {PWM_LOWEST_LEVEL,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,30,40,50,60,70,80,90,100};  // carefully selected through experimentation for best visual fading effect
  unsigned char current_level_idx = 0;
  unsigned int max_len = sizeof(pwm_levels) / sizeof(pwm_levels[0]);

  bool cycle_ongoing;

  while(1)
  {
    // All LEDs are ON! Move to fading them in and out next.
    cycle_ongoing = true;
    
    delay(random(1000, 2000));  // Random delay successive fade in and fade out blocks.

    while(cycle_ongoing)
    {
      PWM_REGISTER = pwm_levels[current_level_idx];
      delay(LED_EFFECT_WAIT_TIME);  // Random delay time between two successive Fade in and out pairs.

      if(count_state == FADE_IN)
      {// we are in FADE_IN phase
        if(current_level_idx == (max_len - 1))
        {// reached the FADE_IN limit
          count_state = FADE_OUT;  // time to switch to FADE_OUT state
          --current_level_idx;  // down one register value to kick off fade out next.
        }
        else
        {// FADE_IN limit not yet reached
          ++current_level_idx;  // up one register value for next fade in period.
        }
      }
      else
      {// we are in the FADE_OUT phase
        if(current_level_idx == 0)
        {// reached the FADE_OUT lower limit
          count_state = FADE_IN;  // time to switch to FADE_IN state
          ++current_level_idx;  // up one register value to kick off fade in next.
          cycle_ongoing = false;  // One fade in fade out cycle finished
        }
        else
        {// FADE_OUT lower limit not yet reached
          --current_level_idx;  // down one register value for next fade out period.
        }
      }

    }// end while cycle_ongoing

  }// end while

}

// the setup function runs once when you press reset or power the board
void setup()
{
  pinMode(FADING_OUT, OUTPUT);
  wait_ms(20);

  // Following ensures at each power up a new light pattern/sequence is generated.
  random_seed_manager();  // update random seed

#if defined(FADER_EFFECT)
  timer_counter_1_pwm_setup();  // Controls FADING_LEDS pin
  enable_LED(FADING_OUT);
  PWM_REGISTER = PWM_LOWEST_LEVEL;
#endif

#ifdef SPARKLE_EFFECT
  disable_LED(FADING_OUT);
#endif

}

// the loop function runs over and over again forever
void loop()
{
  #ifdef SPARKLE_EFFECT
    random_sparkles();
  #endif
  
  #ifdef FADER_EFFECT
    led_fader();  // Includes infinite loop internally
  #endif

}
