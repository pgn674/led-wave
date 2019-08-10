#include "FastLED.h"
#define SLOWNESS 64.0
#define NUM_LEDS 50
#define BRIGHTNESS 1.0
#define SLOW_SPEED = 3.0/3.0
#define MEDIUM_SPEED = 4.0/3.0
#define FAST_SPEED = 5.0/3.0
#define SLOW_DIRECTION 1
#define MEDIUM_DIRECTION 1
#define FAST_DIRECTION 1


// Defaults
// SLOWNESS: 256.0
//     (OR): 64.0
// NUM_LEDS: 50
// BRIGHTNESS: 1.0
// SLOW_SPEED: 3.0/3.0
// MEDIUM_SPEED: 4.0/3.0
// FAST_SPEED: 5.0/3.0
// SLOW_DIRECTION: 1
// MEDIUM_DIRECTION: 1
// FAST_DIRECTION: 1

// Slow is Red
// Medium is Green
// Fast is Blue
// "Slowness" is "How many steps it takes to get from minimum brightness to maximum"

// If you wish to change the speeds, I recomend this method:
// Chose three positive seqencial integers: A, B, C. If these hold true:
// LCM(A,B)=A*B
// LCM(A,C)=A*C
// LCM(B,C)=B*C
// LCM(A,B,C)=A*B*C
// Then you got a good set. Set the speeds like this:
// Slow speed: A/A
// Medium speed: B/A
// Fast speed: C/A
// A higher set of integers will result in a longer pattern before it repeats.
// Some examples are | 3,4,5 | 5,6,7 | 7,8,9 | 9,10,11 |


// Creates fancy array named "leds" of size 1
CRGB leds[NUM_LEDS];
CRGBSet ledset(leds, NUM_LEDS);
//CRGBArray<NUM_LEDS> ledset;

int timey = 0;
int slow;
int medium;
int fast;

void setup() {
  // NEOPIXEL is WS2811
  // Using data pin 6 on the board
  // Uses variable named "leds"
  FastLED.addLeds<WS2811, 6>(leds, NUM_LEDS);

  ledset(0, NUM_LEDS - 1) = CRGB::Black;
  FastLED.show();
  delay(200);
  ledset(0, NUM_LEDS - 1) = CRGB::White;
  FastLED.show();
  delay(200);
  ledset(0, NUM_LEDS - 1) = CRGB::Black;
  FastLED.show();
  delay(200);
}

void loop() {
  for (int led_select = 0; led_select < NUM_LEDS; led_select++) {
    slow = round(((sin((((float)timey * SLOW_DIRECTION + (SLOWNESS / (float)NUM_LEDS) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    medium = round(((sin((((float)timey * MEDIUM_DIRECTION * 4.0 / 3.0 + (SLOWNESS / (float)NUM_LEDS) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    fast = round(((sin((((float)timey * FAST_DIRECTION * 5.0 / 3.0 + (SLOWNESS / (float)NUM_LEDS) * (float)led_select) * 2.0 * PI) / SLOWNESS) + 1.0) / 2.0) * 255.0 * BRIGHTNESS);
    leds[led_select] = CRGB(slow, medium, fast);
  }
  FastLED.show();
  timey++;
}

