#include <FastLED.h> // lib for WS2812 led lights

// there are 3 sets of buttons with 3 button each (9 in total)

#define B1_PIN A0
#define B2_PIN A3
#define B3_PIN A4

// reset button
#define R_PIN A5

int buttonLineValue1 = 0;
int buttonLineValue2 = 0;
int buttonLineValue3 = 0;
int resetButton = 0; 

// if no button is currently being pressed
int lastState = 0;

// signal from button 1.1 is approx 126, for 1.2 is 511 and 1.3 is 1022, same for 2.x and 3.x
const int buttonResistanceBounds[] = {100, 300, 800, 1200};                

// tile state counters and matching table

int idx = 0;

struct tile_t
{
    const uint8_t   tile_id;
    uint8_t         current_color;
    const uint8_t   first_led_id;
    const uint8_t   last_led_id;
};


struct tile_t     tiles[] =
{
      { 0, 0, 0, 0}
    , { 1, 0, 36, 48}
    , { 2, 0, 24, 36}
    , { 3, 0, 12, 24}
    , { 4, 0, 48, 60}
    , { 5, 0, 84, 96}
    , { 6, 0, 0, 12}
    , { 7, 0, 60, 72}
    , { 8, 0, 72, 84}
    , { 9, 0, 96, 108}
};

// LED lights settings
#define NUM_LEDS 108 
#define LED_PIN 13
CRGB leds[NUM_LEDS];   




void setup() {
  FastLED.addLeds <WS2812, LED_PIN, GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(25);
}



void loop() 
{ 
  buttonLineValue1 = analogRead(B1_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue1, 0, lastState);
  if (idx > 0) {
    
    if (tiles[idx].current_color % 2 == 0 )
      MakeBlue(tiles[idx].first_led_id, tiles[idx].last_led_id);
    else
      MakeRed(tiles[idx].first_led_id, tiles[idx].last_led_id);

    tiles[idx].current_color += 1;
  }

  buttonLineValue2= analogRead(B2_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue2, 1, lastState);
  if (idx > 0) {
    
    if (tiles[idx].current_color % 2 == 0 )
      MakeBlue(tiles[idx].first_led_id, tiles[idx].last_led_id);
    else
      MakeRed(tiles[idx].first_led_id, tiles[idx].last_led_id);

    tiles[idx].current_color += 1;
  }

  buttonLineValue3 = analogRead(B3_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue3, 2, lastState);
  if (idx > 0) {
    
    if (tiles[idx].current_color % 2 == 0 )
      MakeBlue(tiles[idx].first_led_id, tiles[idx].last_led_id);
    else
      MakeRed(tiles[idx].first_led_id, tiles[idx].last_led_id);

    tiles[idx].current_color += 1;
  }

  lastState = max(max(buttonLineValue1, buttonLineValue2), buttonLineValue3);

  // reset button
  resetButton = analogRead(R_PIN);
  if (resetButton < 1500 &&  resetButton > 300) {
    TurnOffLED(0, NUM_LEDS);
    for( int i = 1; i < 9; i++) {
      tiles[idx].current_color = 0;
    }
  }
  
}

int GetTileID(int buttonLineValue, int line_id, int lastState) {
    int idx = 0;
    if (buttonLineValue < buttonResistanceBounds[1] &&  buttonLineValue > buttonResistanceBounds[0] && lastState < 10) 
      idx = 1 + line_id * 3;   
    else if (buttonLineValue < buttonResistanceBounds[2] &&  buttonLineValue > buttonResistanceBounds[1] && lastState < 10)
      idx = 2 + line_id * 3;  
    else if (buttonLineValue < buttonResistanceBounds[3] &&  buttonLineValue > buttonResistanceBounds[2] && lastState < 10)
      idx = 3 + line_id * 3;  
    return idx; 
}

void MakeBlue(int a, int b) {
  for( int i = a; i < b; i++) {
    leds[i] = CRGB::Blue;
  }
  FastLED.show();
}

void MakeRed(int a, int b) {
  for( int i = a; i < b; i++) {
    leds[i] = CRGB(139,0,0);
  }
  FastLED.show();
}

void TurnOffLED(int a, int b) {
  for( int i = a; i < b; i++) {
    leds[i] = CRGB(0,0,0);
  }
  FastLED.show();
}
