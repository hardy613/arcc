#include <SoftwareSerial.h>
/**
    @file:  basic set up for blueTooth connection with my phone
            I would like to add a WiiMote in the future
            right now we are just reading the data we send it,
            just need a steering wheel (hence wiimote).

    @uses:  HC-06 BlueTooth Module
            Andriod phone (Nexus 5x)

*/
//bluetooth connection
#define rxPin 4               //bluetooth tx pin
#define txPin 2               //bluetooth rx pin
#define bluetoothStatePin 7   //bluetooth state pin
#define baudRate 115200       //AT+BUAD8 ammount of data we can pass

//L293D Connection
#define steeringMotor1 10 //L293D pin 10
#define steeringMotor2 9  //L293D pin 14
#define driveMotor1 5     //L293D pin 2
#define driveMotor2 6     //L293D pin 7

//bluetooth data
String blueToothVal;

//setting this up allows us to send updates to the
//board without having to remove wires.
SoftwareSerial blueTooth(rxPin, txPin);

/**
 * Begin our serial and bluetooth buad rates
 * Set the State, RX and TX pins for bluetooth comms
 * Set pins for steering and driving motors
 */
void setup()
{
  //bluetooth pins
  pinMode(bluetoothStatePin, INPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  //L293D Pins
  pinMode(steeringMotor1, OUTPUT);
  pinMode(steeringMotor2, OUTPUT);
  pinMode(driveMotor1, OUTPUT);
  pinMode(driveMotor2, OUTPUT);
  //open communication
  Serial.begin(baudRate);
  blueTooth.begin(baudRate);
  
  Serial.println("Starting: ...");
}

void loop()
{
  Serial.flush();
//Uncomment below once we've connected the bluetooth state pin
  if (digitalRead(bluetoothStatePin) == LOW)
  {//bluetooth connection lost
    Serial.print("Connection Lost: ");
    Serial.println(digitalRead(bluetoothStatePin));
    blueTooth.flush();
    blueToothVal = 'S';
    allStopARCC();
  }
  else
  {//we're connected    
    if (blueTooth.available())
    {
      blueToothVal = char(blueTooth.read());
  
      Serial.print("Captured Char: ");
      Serial.println(blueToothVal);
    }
    
    //clear the data for the next cycle
    blueTooth.flush();
    
    if (blueToothVal == "L") 
    {//left
        analogWrite(steeringMotor1, 200);  
        analogWrite(steeringMotor2, 0); 
        analogWrite(driveMotor1, 0);  
        analogWrite(driveMotor2, 0);
    } 
    else if (blueToothVal == "R") 
    {//right
        analogWrite(steeringMotor1, 0);  
        analogWrite(steeringMotor2, 200); 
        analogWrite(driveMotor1, 0);  
        analogWrite(driveMotor2, 0);  
    }
    else if (blueToothVal == "F") 
    {//forward
        analogWrite(steeringMotor1, 0);  
        analogWrite(steeringMotor2, 0); 
        analogWrite(driveMotor1, 200);  
        analogWrite(driveMotor2, 0);  
    }
    else if (blueToothVal == "B") 
    {//forward
        analogWrite(steeringMotor1, 0);  
        analogWrite(steeringMotor2, 0); 
        analogWrite(driveMotor1, 0);  
        analogWrite(driveMotor2, 200);  
    }
    else 
    {
      allStopARCC();
    }
  }
  //we can get 2 char from our connection with this
  //if we remove it we can sometimes only get one char
  delay(50);
}

/**
 * Let's be careful and try to keep the car safe
 * Turns off all motors
 */
void allStopARCC() 
{
  //make it so number 1
  analogWrite(steeringMotor1, 0);  
  analogWrite(steeringMotor2, 0); 
  analogWrite(driveMotor1, 0);  
  analogWrite(driveMotor2, 0);
}


