 //v12345vtm   https://www.youtube.com/watch?v=S3Zgnuk0Kfc

#include "OneButton.h"

// Setup a new OneButton on pin A1.
OneButton button1(A1, true);
// Setup a new OneButton on pin A2.
OneButton button2(A2, true);

#include <FastLED.h>

// How many leds in your strip?
#define NUM_LEDS 32
#define DATA_PIN 8
const int ledPin = 13;      // the number of the LED pin

// Define the array of leds
CRGB leds[NUM_LEDS];

unsigned long eventInterval = 1070;
unsigned long previousTime = 0;

String standvzaken = "uit";
int stand;

byte prioriteit = 255 ; //hoe lager het getal hoe belanrijker 0= noodstop bijvoorbeeld
int x ;// we mogen geen for loops gebruiken

// toggle Variables will change:
byte TurnLEFT = LOW;         // the current state of the output pin
byte TurnRIGHT = LOW;

void setup() {

  stand = 0;
  x = 0;
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);


  // link the button 1 functions.
  button1.attachClick(click1);
  button1.attachDoubleClick(doubleclick1);
  button1.attachLongPressStart(longPressStart1);
  button1.attachLongPressStop(longPressStop1);
  button1.attachDuringLongPress(longPress1);

  // link the button 2 functions.
  button2.attachClick(click2);
  button2.attachDoubleClick(doubleclick2);
  button2.attachLongPressStart(longPressStart2);
  button2.attachLongPressStop(longPressStop2);
  button2.attachDuringLongPress(longPress2);

  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);  // GRB ordering is assumed
  // https://alloyui.com/examples/color-picker/hsv.html

  FastLED.clear();  // clear all pixel data
  FastLED.show();

  Serial.print("kleverpinker3");
  Serial.println("Starting TwoButtons...");


  //startseq
  for (byte x = 0; x < 8; x++) {
    leds[x] = CHSV(27, 255, 20); //front links
    leds[x + 16] = CHSV(27, 255, 20); //rear links
    leds[15 - x] = CHSV(27, 255, 20); //fronr rechts
    leds[31 - x] = CHSV(27, 255, 20); //rear rechts
    FastLED.show();
    delay(100);
  }
  FastLED.clear();  // clear all pixel data
  FastLED.show();
  delay(250);


  FastLED.clear();  // clear all pixel data
  FastLED.show();
  delay(250);


  // while (1) {}
}

void loop() {  //https://github.com/FastLED/FastLED/wiki/FastLED-HSV-Colors

  /* Updates frequently */
  unsigned long currentTime = millis();

  // keep watching the push buttons:
  button1.tick();
  button2.tick();

  /* This is the event */
  if (currentTime - previousTime >= eventInterval) {
    /* Event code */
    Serial.print (standvzaken);
    Serial.print (" stand= " );
    Serial.print (stand);
    Serial.print (" x= " );
    Serial.println (x);

    //cases
    if (stand  == 5) {
      x = 0;
      FastLED.clear();  // clear all pixel data
      FastLED.show();
    }

    if (stand  == 1) {
      knipperrechts();
      FastLED.show();
      x = x + 1;
    }



    if (stand  == 2) {
      knipperlinks();
      FastLED.show();
      x = x + 1;
    }


    if (stand  == 4) {
      hazard();//4pinkers
      FastLED.show();
      x = x + 1;
    }


    if (stand  == 0) {
      gewoonrijden();//
      FastLED.show();
      x = x + 1;
    }

    /* Update the timing for the next time around */
    previousTime = currentTime;
  }
}


// ----- button 1 callback functions

// This function will be called when the button1 was pressed 1 time (and no 2. button press followed).
void click1() {

  prioriteit = 1 ;
  TurnRIGHT = LOW ; //de andere richting afleggen moest dit aan zijn


  TurnLEFT = !TurnLEFT;

  Serial.println("Button 1 click. LEFT " +   String(prioriteit) + " " + TurnLEFT);
  if (TurnLEFT) {
    standvzaken = "pinkt TurnLEFT";
    stand = 2 ;
    x = 0;
  }
  if (!TurnLEFT) {
    standvzaken = "uit";
    stand = 0 ;
  }

} // click1


// This function will be called when the button1 was pressed 2 times in a short timeframe.
void doubleclick1() {
  Serial.println("Button 1 doubleclick.");
  standvzaken = "uit";
  stand = 5 ;
} // doubleclick1


// This function will be called once, when the button1 is pressed for a long time.
void longPressStart1() {
  Serial.println("Button 1 longPress start");
} // longPressStart1


// This function will be called often, while the button1 is pressed for a long time.
void longPress1() {
  // Serial.println("Button 1 longPress...");
  standvzaken = "drive";
  stand = 0 ;
  TurnLEFT = LOW;         // moesten we hierna willen een pinker aanleggen kan dit
  TurnRIGHT = LOW;
} // longPress1


// This function will be called once, when the button1 is released after beeing pressed for a long time.
void longPressStop1() {
  Serial.println("Button 1 longPress stop");

} // longPressStop1


// ... and the same for button 2:

void click2() {
  prioriteit = 1 ;
  TurnLEFT = LOW ; //de andere richting afleggen moest dit aan zijn
  TurnRIGHT = ! TurnRIGHT;
  Serial.println("Button 2 click. RIGHT " +   String(prioriteit) + " " + TurnRIGHT);
  if (TurnRIGHT) {
    standvzaken = "pinkt TurnRIGHT";
    stand = 1 ;
    x = 0 ;
  }
  if (!TurnRIGHT) {
    standvzaken = "uit";
    stand = 0 ;
  }
} // click2


void doubleclick2() {
  Serial.println("Button 2 doubleclick.");
  standvzaken = "alle pinkers";
  stand = 4 ;
} // doubleclick2


void longPressStart2() {
  Serial.println("Button 2 longPress start");
} // longPressStart2


void longPress2() {
  // Serial.println("Button 2 longPress...");
  standvzaken = "uit";
  stand = 0 ;
  TurnLEFT = LOW;         // moesten we hierna willen een pinker aanleggen kan dit
  TurnRIGHT = LOW;
} // longPress2

void longPressStop2() {
  Serial.println("Button 2 longPress stop");

} // longPressStop2



void knipperrechts()
{

  if (x == 0)
  {
    FastLED.clear();  // clear all pixel data
    FastLED.show();
  }


  if (x < 8)
  {
    // Serial.print ("    stand= " );
    // Serial.println (stand);
    leds[x] = CHSV(0, 0, 0); //front links
    leds[x + 16] = CHSV(0, 0, 0); //rear links
    leds[x + 8] = CHSV(27, 255, 100); //fronr rechts
    leds[x + 24] = CHSV(27, 255, 100); //rear rechts
    eventInterval = 70;
  }
  else {
    x = 0 - 1;
    FastLED.clear();  // clear all pixel data
    FastLED.show();
    eventInterval = 200;
  }
}



void knipperlinks()
{

  if (x == 0)
  {
    FastLED.clear();  // clear all pixel data
    FastLED.show();
  }

  if (x < 8)
  {
    // Serial.print ("    stand= " );
    // Serial.println (stand);
    leds[8 + x] = CHSV(0, 0, 0); //front links
    leds[24 + x] = CHSV(0, 0, 0); //rear links
    leds[7 - x] = CHSV(27, 255, 100); //fronr rechts
    leds[23 - x] = CHSV(27, 255, 100); //rear rechts
    eventInterval = 70;
  }
  else {
    x = 0 - 1;
    FastLED.clear();  // clear all pixel data
    FastLED.show();
    eventInterval = 200;
  }
}


void   hazard() {
  if (x == 0)
  {
    FastLED.clear();  // clear all pixel data
    FastLED.show();
    TurnLEFT = LOW;         // moesten we hierna willen een pinker aanleggen kan dit
    TurnRIGHT = LOW;
  }
  if (x < 1)
  {
    for (byte y = 0; y < 32; y++) {
      leds[y] =  CHSV(27, 255, 100); //eerst alles wit
      FastLED.show();
    }
    eventInterval = 170;
  }
  else {
    x = 0 - 1;
    FastLED.clear();  // clear all pixel data
    FastLED.show();
    eventInterval = 200;
  }
}




void   gewoonrijden() {

  TurnLEFT = LOW;         // moesten we hierna willen een pinker aanleggen kan dit
  TurnRIGHT = LOW;

  if (true)
  {
    for (byte y = 0; y < 16; y++) {
      leds[y] = CHSV(130, 50, 15); //front wit
        leds[y+16] = CHSV(255, 255, 5); //rear rood
      FastLED.show();
    }

    
    //   eventInterval = 170;
  }

}
