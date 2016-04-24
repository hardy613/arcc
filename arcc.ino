/**
 * @file: basic set up for blueTooth connection with my phone
 *        I would like to add a WiiMote in the future
 *        
 */

#include <SoftwareSerial.h>

#define rxPin 4

#define txPin 2

#define ledPin 13

#define baudRate 115200

SoftwareSerial blueTooth(rxPin, txPin);

char blueToothVal;

String blueToothMessage;

/**
 * 
 */
void setup()
{
 Serial.begin(baudRate);

 blueTooth.begin(baudRate);
 
 pinMode(rxPin, INPUT);
 
 pinMode(txPin, OUTPUT);
 
 pinMode(ledPin, OUTPUT); 
 
 Serial.println("Starting: ...");
}
 
/**
 * 
 */
void loop()
{
  Serial.flush();

  blueTooth.flush();
  
  if (!blueTooth.available()) return;
  
  while(blueTooth.available()) 
  {
    blueToothVal = blueTooth.read(); //read it
  
    blueToothMessage += blueToothVal;
    
    Serial.print("Captured Char: ");
    
    Serial.println(blueToothVal);
    
    blueToothVal = NULL;
  }

  if(blueToothMessage.length()) 
  {
    Serial.print("Captured Message: ");
    
    Serial.println(blueToothMessage);

    Serial.print("Captured Message Length: ");
    
    Serial.println(blueToothMessage.length());

    Serial.println(" ");

    Serial.println(" ");
    
    blueToothMessage = "";
  }

  //we can get 2 char from our connection with this
  //if we remove it we can sometimes only get one char
  delay(5);
}


