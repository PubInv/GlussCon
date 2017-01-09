
//////////////////////
// Library Includes //
//////////////////////
// SoftwareSerial is required (even you don't intend on
// using it).
#include <SoftwareSerial.h> 
#include <SparkFunESP8266WiFi.h>

//////////////////////////////
// WiFi Network Definitions //
//////////////////////////////
// Replace these two character strings with the name and
// password of your WiFi network.
const char mySSID[] = "readfamilynetwork";
const char myPSK[] = "magicalsparrow96";

//////////////////////////////
// ESP8266Server definition //
//////////////////////////////
// server object used towards the end of the demo.
// (This is only global because it's called in both setup()
// and loop()).
ESP8266Server server = ESP8266Server(80);

//////////////////
// HTTP Strings //
//////////////////
const char destServer[] = "example.com";
const String  htmlHeader = "HTTP/1.1 200 OK\r\n"
                          "Content-Type: text/html\r\n"
                          "Connection: close\r\n\r\n"
                          "<!DOCTYPE HTML>\r\n"
                          "<html>\r\n";

const String httpRequest = "GET / HTTP/1.1\n"
                           "Host: example.com\n"
                           "Connection: close\n\n";

                           
// Contstant definitions
int POTPIN = A0;             // analog pins used for the potentiometer

int NUM_POTS = 6;            // number of potentiometers in the design
// int MUX_SEL[] = {5,3};       // digital outputs pins for selecting a mux line

//Mux control pins
int s0 = 2;
int s1 = 3;
int s2 = 4;
int s3 = 5;

void setup() {
  // put your setup code here, to run once:
//  pinMode(MUX_SEL[0], OUTPUT);
//  pinMode(MUX_SEL[1], OUTPUT);


  pinMode(s0, OUTPUT); 
  pinMode(s1, OUTPUT); 
  pinMode(s2, OUTPUT); 
  pinMode(s3, OUTPUT); 

  digitalWrite(s0, LOW);
  digitalWrite(s1, LOW);
  digitalWrite(s2, LOW);
  digitalWrite(s3, LOW);
  
  pinMode(13,OUTPUT);

    // Serial Monitor is used to control the demo and view
  // debug information.
  Serial.begin(9600);
  serialTrigger(F("Press any key to begin."));

  // initializeESP8266() verifies communication with the WiFi
  // shield, and sets it up.
  initializeESP8266();

  // connectESP8266() connects to the defined WiFi network.
  connectESP8266();

  // displayConnectInfo prints the Shield's local IP
  // and the network it's connected to.
  displayConnectInfo();
  
  serialTrigger(F("Press any key to test server."));
  serverSetup();
}

/*************************************************
 *    Function:    loop
 *    Description: Continuously reads the values of
 *                 the potentiometers and sends them
 *                 to the GLUSSBOT
 */
void loop() {
  serverDemo();  
}

/******************************************
 *    Function: readpot
 *    Description: reads the value from the 
 *    specified potentiometer.
 */
//int readpot(int potnum) {
//  if (potnum == 0) {
//      digitalWrite(MUX_SEL[0], LOW);
//      digitalWrite(MUX_SEL[1], LOW);
//  } else if (potnum == 1) {
//      digitalWrite(MUX_SEL[0], HIGH);
//      digitalWrite(MUX_SEL[1], LOW);
//  } else if (potnum == 2) {
//      digitalWrite(MUX_SEL[0], LOW);
//      digitalWrite(MUX_SEL[1], HIGH);
//  }
//  
//  return analogRead(POTPIN);
//}

//Mux control pins
//int s0 = 8;
//int s1 = 9;
//int s2 = 10;
//int s3 = 11;

//Mux in "SIG" pin
int SIG_pin = 0;

//
//void setup(){
//  pinMode(s0, OUTPUT); 
//  pinMode(s1, OUTPUT); 
//  pinMode(s2, OUTPUT); 
//  pinMode(s3, OUTPUT); 
//
//  digitalWrite(s0, LOW);
//  digitalWrite(s1, LOW);
//  digitalWrite(s2, LOW);
//  digitalWrite(s3, LOW);
//
//  Serial.begin(9600);
//}

//
//void loop(){
//
//  //Loop through and read all 16 values
//  //Reports back Value at channel 6 is: 346
//  for(int i = 0; i < 16; i ++){
//    Serial.print("Value at channel ");
//    Serial.print(i);
//    Serial.print("is : ");
//    Serial.println(readMux(i));
//    delay(1000);
//  }
//
//}


int readMux(int channel){
  int controlPin[] = {s0, s1, s2, s3};

  int muxChannel[16][4]={
    {0,0,0,0}, //channel 0
    {1,0,0,0}, //channel 1
    {0,1,0,0}, //channel 2
    {1,1,0,0}, //channel 3
    {0,0,1,0}, //channel 4
    {1,0,1,0}, //channel 5
    {0,1,1,0}, //channel 6
    {1,1,1,0}, //channel 7
    {0,0,0,1}, //channel 8
    {1,0,0,1}, //channel 9
    {0,1,0,1}, //channel 10
    {1,1,0,1}, //channel 11
    {0,0,1,1}, //channel 12
    {1,0,1,1}, //channel 13
    {0,1,1,1}, //channel 14
    {1,1,1,1}  //channel 15
  };

  //loop through the 4 sig
  for(int i = 0; i < 4; i ++){
    digitalWrite(controlPin[i], muxChannel[channel][i]);
//    Serial.print(controlPin[i]);
 //   Serial.print(" ");
 //   Serial.println( muxChannel[channel][i]);
  }
  // Just want to give Mux time to settle on new voltage...
  delay(10);

  //read the value at the SIG pin
  int val = analogRead(SIG_pin);

  //return the value
  return val;
}

void initializeESP8266()
{
  // esp8266.begin() verifies that the ESP8266 is operational
  // and sets it up for the rest of the sketch.
  // It returns either true or false -- indicating whether
  // communication was successul or not.
  // true
  int test = esp8266.begin();
  if (test != true)
  {
    Serial.println(F("Error talking to ESP8266."));
    errorLoop(test);
  }
  Serial.println(F("ESP8266 Shield Present"));
}

void connectESP8266()
{
  // The ESP8266 can be set to one of three modes:
  //  1 - ESP8266_MODE_STA - Station only
  //  2 - ESP8266_MODE_AP - Access point only
  //  3 - ESP8266_MODE_STAAP - Station/AP combo
  // Use esp8266.getMode() to check which mode it's in:
  int retVal = esp8266.getMode();
  if (retVal != ESP8266_MODE_STA)
  { // If it's not in station mode.
    // Use esp8266.setMode([mode]) to set it to a specified
    // mode.
    retVal = esp8266.setMode(ESP8266_MODE_STA);
    if (retVal < 0)
    {
      Serial.println(F("Error setting mode."));
      errorLoop(retVal);
    }
  }
  Serial.println(F("Mode set to station"));

  // esp8266.status() indicates the ESP8266's WiFi connect
  // status.
  // A return value of 1 indicates the device is already
  // connected. 0 indicates disconnected. (Negative values
  // equate to communication errors.)
  retVal = esp8266.status();
  if (retVal <= 0)
  {
    Serial.print(F("Connecting to "));
    Serial.println(mySSID);
    // esp8266.connect([ssid], [psk]) connects the ESP8266
    // to a network.
    // On success the connect function returns a value >0
    // On fail, the function will either return:
    //  -1: TIMEOUT - The library has a set 30s timeout
    //  -3: FAIL - Couldn't connect to network.
    retVal = esp8266.connect(mySSID, myPSK);
    if (retVal < 0)
    {
      Serial.println(F("Error connecting"));
      errorLoop(retVal);
    }
  }
}

void displayConnectInfo()
{
  char connectedSSID[24];
  memset(connectedSSID, 0, 24);
  // esp8266.getAP() can be used to check which AP the
  // ESP8266 is connected to. It returns an error code.
  // The connected AP is returned by reference as a parameter.
  int retVal = esp8266.getAP(connectedSSID);
  if (retVal > 0)
  {
    Serial.print(F("Connected to: "));
    Serial.println(connectedSSID);
  }

  // esp8266.localIP returns an IPAddress variable with the
  // ESP8266's current local IP address.
  IPAddress myIP = esp8266.localIP();
  Serial.print(F("My IP: ")); Serial.println(myIP);
}

void serverSetup()
{
  // begin initializes a ESP8266Server object. It will
  // start a server on the port specified in the object's
  // constructor (in global area)
  server.begin();
  Serial.print(F("Server started! Go to "));
  Serial.println(esp8266.localIP());
  Serial.println();
}

void serverDemo()
{
  // available() is an ESP8266Server function which will
  // return an ESP8266Client object for printing and reading.
  // available() has one parameter -- a timeout value. This
  // is the number of milliseconds the function waits,
  // checking for a connection.
  ESP8266Client client = server.available(500);
  
  if (client) 
  {
    Serial.println(F("Client Connected!"));
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) 
    {
      if (client.available()) 
      {
        char c = client.read();
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) 
        {
          Serial.println(F("Sending HTML page"));
          // send a standard http response header:
          client.print(htmlHeader);
          String htmlBody;
          // output the value of each analog input to the mux
          htmlBody += "{ \n";
          for (int potnum = 0; potnum < NUM_POTS ; potnum++)
          {
            // read value of the selected potentiometer
            int dist = readMux(potnum);

            htmlBody += String("\"A");
            htmlBody += String(potnum);
            htmlBody += String("\"");
            htmlBody += ": \"";
            htmlBody += String(dist);
            htmlBody += "\"";
            if (potnum < NUM_POTS-1) {
              htmlBody += ",\n";
            }
          }
          htmlBody += " }\n";
          client.print(htmlBody);
//          delay(10);
//          while (client.available()) {
//            c = client.read();
//            delay(10);
//            Serial.println(c);
//          }
          break;
        }
        if (c == '\n') 
        {
          // you're starting a new line
          currentLineIsBlank = true;
        }
        else if (c != '\r') 
        {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    
    
    // give the web browser time to receive the data
    delay(500);
//   
    // close the connection:
    client.stop();
    Serial.println(F("Client disconnected"));
//
//      // Let's see if the client is unavailable as it should be...
//    delay(1000);
//    Serial.println("Are we available?");
//    Serial.println(client.available());
//    Serial.println("Are we connected?");
//    Serial.println(client.connected());
  }
  
}

// errorLoop prints an error code, then loops forever.
void errorLoop(int error)
{
  Serial.print(F("Error: ")); Serial.println(error);
  Serial.println(F("Looping forever."));
  for (;;)
    ;
}

// serialTrigger prints a message, then waits for something
// to come in from the serial port.
void serialTrigger(String message)
{
  Serial.println();
  Serial.println(message);
  Serial.println();
  while (!Serial.available())
    ;
  while (Serial.available())
    Serial.read();
}
