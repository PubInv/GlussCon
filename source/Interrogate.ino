int POTPIN = A0;             // analog pins used for the potentiometer
int NUM_POTS = 3;            // number of potentiometers in the design
int MUX_SEL[] = {5,3};       // digital outputs pins for selecting a mux line

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(MUX_SEL[0], OUTPUT);
  pinMode(MUX_SEL[1], OUTPUT);

  pinMode(13,OUTPUT);
  
}

/*************************************************
 *    Function:    loop
 *    Description: Continuously reads the values of
 *                 the potentiometers and sends them
 *                 to the GLUSSBOT
 */
void loop() {
  // put your main code here, to run repeatedly:
  int pots[NUM_POTS];
  digitalWrite(13, HIGH);
  
  for (int potnum=0; potnum < NUM_POTS; potnum++) {
    // read value of the selected potentiometer
    int dist = readpot(potnum);
    // sendpotposition(potnum,dist);
    Serial.println(dist);    
    delay(1000);
  }
   
  //int pot0 = analogRead(POTPIN);   // Read the value of the potentiometer
  
  
  
}

/******************************************
 *    Function: readpot
 *    Description: reads the value from the 
 *    specified potentiometer.
 */
int readpot(int potnum) {
  if (potnum == 0) {
      Serial.println("sel 0");
      digitalWrite(MUX_SEL[0], LOW);
      digitalWrite(MUX_SEL[1], LOW);
  } else if (potnum == 1) {
      Serial.println("sel 1");
      digitalWrite(MUX_SEL[0], HIGH);
      digitalWrite(MUX_SEL[1], LOW);
  } else if (potnum == 2) {
      Serial.println("sel 2");
      digitalWrite(MUX_SEL[0], LOW);
      digitalWrite(MUX_SEL[1], HIGH);
  }
  
  
  /*switch(potnum) {
    case 0:
      Serial.println("sel 0");
      digitalWrite(MUX_SEL[0], LOW);
      digitalWrite(MUX_SEL[1], LOW);
    case 1:
      Serial.println("sel 1");
      digitalWrite(MUX_SEL[0], HIGH);
      digitalWrite(MUX_SEL[1], LOW);
    case 2:
      Serial.println("sel 2");
      digitalWrite(MUX_SEL[0], LOW);
      digitalWrite(MUX_SEL[1], HIGH);
  }*/
  return analogRead(POTPIN);
}



