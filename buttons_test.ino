const uint8_t   pinBUTTON_1 = A0;
const uint8_t   pinBUTTON_2 = A1;
const uint8_t   pinBUTTON_3 = A2;

struct button_t
{
    const uint8_t   pin;
    uint8_t         stateLast;
};

struct button_t     buttons[] =
{
      { pinBUTTON_1, 0}
    , { pinBUTTON_2, 0}
    , { pinBUTTON_3, 0}
};

int pushButton(struct button_t* button)
{   
    uint8_t state = analogRead(A0);
    if ( state < 300 && state > 100 && (*button).stateLast < 10 )
    {
        Serial.println("button 1 is pushed");
        Serial.println(state);
    }

    else if ( state < 800 && state > 300 && (*button).stateLast < 0 )
    {
        Serial.println("button 2 is pushed");
        Serial.println(state);
    }

    else if ( state < 1200 && state > 800 && (*button).stateLast < 0 )
    {
        Serial.println("button 3 is pushed");
        Serial.println(state);
    }

    (*button).stateLast = state;

    return 0;
}

void loop()
{
  
  pushButton(&buttons[0]);
  pushButton(&buttons[1]);
  pushButton(&buttons[2]);

}

void setup()
{
    Serial.begin(9600);
}
