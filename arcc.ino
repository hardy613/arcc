#include <SoftwareSerial.h>
/**
   @file: basic set up for blueTooth connection with my phone
          I would like to add a WiiMote in the future
          The module we are connecting to is an HC-06 BlueTooth chip;
          right now we are just reading the data we send it, just need a
          steering wheel (hence wiimote).
*/

#define rxPin 4

#define txPin 2

//AT+BUAD8
#define baudRate 115200

char blueToothVal;

String blueToothMessage;

//setting this up allows us to send updates to the
//board without having to remove and wires.
SoftwareSerial blueTooth(rxPin, txPin);

/**

*/
void setup()
{
  Serial.begin(baudRate);

  blueTooth.begin(baudRate);

  pinMode(rxPin, INPUT);

  pinMode(txPin, OUTPUT);

  Serial.println("Starting: ...");
}

/**

*/
void loop()
{
  Serial.flush();

  blueTooth.flush();

  if (!blueTooth.available())
  {//end if there is nothing to read
    return;
  }

  while (blueTooth.available())
  {//we read the char and add it to the string
    blueToothVal = blueTooth.read();

    blueToothMessage += blueToothVal;

    Serial.print("Captured Char: ");

    Serial.println(blueToothVal);

    blueToothVal = NULL;
  }

  if (blueToothMessage.length())
  {//output captured data to the serial montior
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


