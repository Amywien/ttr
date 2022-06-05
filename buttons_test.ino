#define B1_PIN A0
#define B2_PIN A3
#define B3_PIN A5

// reset button
#define R_PIN A6

int buttonLineValue1 = 0;
int buttonLineValue2 = 0;
int buttonLineValue3 = 0;
int resetButton = 0; 

// if no button is currently being pressed
int lastState = 0;

// signal from button 1.1 is approx 126, for 1.2 is 511 and 1.3 is 1022, same for 2.x and 3.x
const int buttonResistanceBounds[] = {10, 100, 300, 800, 1200};                

// tile state counters and matching table

int idx = 0;

struct tile_t
{
    const int   tile_id;
    int         current_color;
    const int   first_led_id;
    const int   last_led_id;
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

void setup() {
  Serial.begin(9600);

}

void loop() { 
  buttonLineValue1 = analogRead(B1_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue1, 0, lastState);
  if (idx > 0) {

    tiles[idx].current_color += 1;
    
    Serial.print("The button is ");
    Serial.println(idx);
    Serial.print("The value is ");
    Serial.println(buttonLineValue1);
    Serial.print("The color is ");
    Serial.println(tiles[idx].current_color);
    
  }

  buttonLineValue2= analogRead(B2_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue2, 1, lastState);
  if (idx > 0) {

    tiles[idx].current_color += 1;
    
    Serial.print("The button is ");
    Serial.println(idx);
    Serial.print("The value is ");
    Serial.println(buttonLineValue2);
    Serial.print("The color is ");
    Serial.println(tiles[idx].current_color);
  }

  buttonLineValue3 = analogRead(B3_PIN);  //Read in the button value
  idx = GetTileID(buttonLineValue3, 2, lastState);
  if (idx > 0) {

    tiles[idx].current_color += 1;
    
    Serial.print("The button is ");
    Serial.println(idx);
    Serial.print("The value is ");
    Serial.println(buttonLineValue3);
    Serial.print("The color is ");
    Serial.println(tiles[idx].current_color);
  }

  lastState = max(max(buttonLineValue1, buttonLineValue2), buttonLineValue3);

    // reset button
  resetButton = analogRead(R_PIN);
  if (resetButton >buttonResistanceBounds[3]) {
    Serial.print("The button is ");
    Serial.println("Reset");
    Serial.print("The value is ");
    Serial.println(resetButton);
    for( int i = 1; i < 9; i++) {
      tiles[i].current_color = 0;
      Serial.print("For tile number ");
      Serial.println(i);
      Serial.print("color is reset to ");
      Serial.println(tiles[idx].current_color);
    }
    }

}

int GetTileID(int buttonLineValue, int line_id, int lastState) {
    int idx = 0;
    if (buttonLineValue < buttonResistanceBounds[2] &&  buttonLineValue > buttonResistanceBounds[1] && lastState < buttonResistanceBounds[0]) 
      idx = 1 + line_id * 3;   
    else if (buttonLineValue < buttonResistanceBounds[3] &&  buttonLineValue > buttonResistanceBounds[2] && lastState < buttonResistanceBounds[0])
      idx = 2 + line_id * 3;  
    else if (buttonLineValue < buttonResistanceBounds[4] &&  buttonLineValue > buttonResistanceBounds[3] && lastState < buttonResistanceBounds[0])
      idx = 3 + line_id * 3;  
    return idx; 
}
