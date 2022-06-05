#include <FastLED.h> // lib for WS2812 led lights

// LED lights settings
#define NUM_LEDS 108 
#define LED_PIN 3
CRGB leds[NUM_LEDS];   




void setup() {
  FastLED.addLeds <WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(25);
}

void loop() {
  delay(1000);
  MakeRed(0,108);
  delay(5000);
  MakeBlue(0,108);
  delay(5000);

}

void MakeRed(int a, int b) {
  for( int i = a; i < b; i++) {
    leds[i] = CRGB(139,0,0);
  }
  FastLED.show();
}

void MakeBlue(int a, int b) {
  for( int i = a; i < b; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
}
