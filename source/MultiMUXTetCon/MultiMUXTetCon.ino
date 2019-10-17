/******************************************************************************
Mux_Analog_Output
SparkFun Multiplexer Output Example
Jim Lindblom @ SparkFun Electronics
August 15, 2016
https://github.com/sparkfun/74HC4051_8-Channel_Mux_Breakout

This sketch demonstrates how to use the SparkFun Multiplexer
Breakout - 8 Channel (74HC4051) to drive eight outputs using
four digital pins.

Hardware Hookup:
Mux Breakout ----------- Arduino
     S0 ------------------- 2
     S1 ------------------- 3
     S2 ------------------- 4
     Z -------------------- 5
    VCC ------------------- 5V
    GND ------------------- GND
    (VEE should be connected to GND)

Development environment specifics:
Arduino 1.6.9
SparkFun Multiplexer Breakout - 8-Channel(74HC4051) v10
(https://www.sparkfun.com/products/13906)
******************************************************************************/
/////////////////////
// Pin Definitions //
/////////////////////
// The first MUX uses 2,3,4, the next uses 5,6,7
const int NUM_BOARDS = 2;
const int selectPins[][3] = { {2, 3, 4},        // S0~2, S1~3, S2~4
                              {5, 6, 7} };

const int zInput[4] = {A0,A1,A2,A3};

const int LED_ON_TIME = 500; // Each LED is on 0.5s
const int DELAY_TIME = ((float)LED_ON_TIME/512.0)*1000;
void setup() 
{
  Serial.begin(115200);
  // Set up the select pins, as outputs
  for(int j = 0; j < NUM_BOARDS; j++) {
    for (int i=0; i<3; i++)
    {
      pinMode(selectPins[j][i], OUTPUT);
      digitalWrite(selectPins[j][i], LOW);
    }
  }
  for (int i=0; i<4; i++)
  {
      pinMode(zInput[4], INPUT); // Set up Z as an input
  }
}

int incomingByte = 0;
int NUMBER_OF_CHANNELS_PER_MUX = 6;
void loop() 
{
  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    Serial.println("XXX");
    Serial.println(selectPins[1][2]);

    // say what you got:
    Serial.print("I received: ");
    Serial.println(incomingByte, DEC);
    if (incomingByte == '\n') {
      for(int j = 0; j < NUM_BOARDS; j++) {
        Serial.print("Board #");
        Serial.println(j);
        for(int i = 0; i < NUMBER_OF_CHANNELS_PER_MUX; i++) {
          selectBrdMuxPin(j,i);
          delay(20);
          int val;
          val = analogRead(zInput[j]);
//          Serial.println(zInput[j]);
          Serial.print("pin ");
          Serial.print(i);
          Serial.print(" = ");
          Serial.println(val);
        }
      }
    }
  }
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectBrdMuxPin(int brd,byte pin)
{
  if (pin >= NUMBER_OF_CHANNELS_PER_MUX) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    //Serial.println("AAAA");
    //Serial.println(selectPins[brd][i]);
    if (pin & (1<<i))
      digitalWrite(selectPins[brd][i], HIGH);
    else
      digitalWrite(selectPins[brd][i], LOW);
  }
}

// The selectMuxPin function sets the S0, S1, and S2 pins
// accordingly, given a pin from 0-7.
void selectMuxPin(byte pin)
{
  if (pin > 7) return; // Exit if pin is out of scope
  for (int i=0; i<3; i++)
  {
    if (pin & (1<<i))
      digitalWrite(selectPins[i], HIGH);
    else
      digitalWrite(selectPins[i], LOW);
  }
}
