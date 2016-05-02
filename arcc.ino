#include <SoftwareSerial.h>
/**
    @file:  basic set up for blueTooth connection with my phone
            I would like to add a WiiMote in the future
            right now we are just reading the data we send it,
            just need a steering wheel (hence wiimote).

    @uses:  HC-06 BlueTooth Module
            Andriod phone (Nexus 5x)

*/
#define rxPin 4

#define txPin 2

//AT+BUAD8
#define baudRate 115200

char blueToothVal;

String blueToothMessage;

//setting this up allows us to send updates to the
//board without having to remove wires.
SoftwareSerial blueTooth(rxPin, txPin);

/**
   Set our serial and bluetooth buad rates
   Set the RX and TX pins for bluetooth comms
*/
void setup()
{
  Serial.begin(baudRate);

  blueTooth.begin(baudRate);

  pinMode(rxPin, INPUT);

  pinMode(txPin, OUTPUT);

  Serial.println("Starting: ...");
}

void loop()
{
  Serial.flush();

  blueTooth.flush();

  Serial.print("blueTooth connedted: ");

  Serial.println(blueTooth.connected());

  if (!blueTooth.available())
  { //end if there is nothing to read
    Serial.print("blueTooth connedted: ");

    Serial.println(blueTooth.connected());

    return;
  }

  while (blueTooth.available())
  { //we read the char and add it to the string
    blueToothVal = blueTooth.read();

    blueToothMessage += blueToothVal;

    Serial.print("Captured Char: ");

    Serial.println(blueToothVal);

    blueToothVal = NULL;
  }

  if (blueToothMessage.length())
  { //output captured data to the serial montior
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
  delay(100);
}


