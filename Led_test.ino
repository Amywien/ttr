#include <FastLED.h> // подключаем библиотеку

#define NUM_LEDS 108 // указываем количество светодиодов на ленте
#define PIN 13                    // указываем пин для подключения ленты

int a = 0;
int b = NUM_LEDS;

CRGB leds[NUM_LEDS];

void setup() {
  Serial.begin(9600);
  // основные настройки для адресной ленты
  FastLED.addLeds <WS2812, PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(25);
  pinMode(resetButtonPin, INPUT);
}

void loop() {
  MakeRed(a, b);
  delay(10000);
  MakeBlue(a, b);
  delay(10000);
}


void MakeRed(int a, int b) {
  for ( int i = a; i < b; i++) {
    leds[i] = CRGB::Red;
  }
  FastLED.show();
}

void MakeBlue(int a, int b) {
  for ( int i = a; i < b; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
}
