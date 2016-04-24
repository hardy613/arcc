#include <SoftwareSerial.h>
#define rxPin 4
#define txPin 2
#define ledPin 13

SoftwareSerial BT(rxPin, txPin);

char blueToothVal;           //value sent over via bluetooth
String btMessage;
 
void setup()
{
 Serial.begin(115200);
 pinMode(rxPin, INPUT);
 pinMode(txPin, OUTPUT);
 pinMode(ledPin, OUTPUT);
 BT.begin(115200); 
 Serial.println("Starting: ...");
}
 
 
void loop()
{

  Serial.flush();
  BT.flush();
  
  if (!BT.available()) return;
  
  while(BT.available()) {
    blueToothVal = BT.read(); //read it
    btMessage += blueToothVal;
    Serial.print("Captured Char: ");
    Serial.println(blueToothVal);
    blueToothVal = NULL;
  }
  
  if (btMessage == "on") {
    
    digitalWrite(ledPin, HIGH); //switch on LED   
  } else if (btMessage == "off") {
    
    digitalWrite(ledPin, LOW); //turn off LED
  } else if (btMessage == "flash") {

      for(int i = 0; i < 10; i++) {

          digitalWrite(ledPin, HIGH);
          delay(100);
          digitalWrite(ledPin, LOW);
          delay(50);
      }

  }

  

  if(btMessage.length()) {
    Serial.print("Captured Message: ");
    Serial.println(btMessage);
    btMessage = "";
  }
  
  delay(1000);
  
}
