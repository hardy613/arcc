#include <SoftwareSerial.h>
//my libraries
#include "Arcc.h"
/**
	@file:  basic set up for blueTooth connection with my phone
	I would like to add a WiiMote in the future
	right now we are just reading the data we send it,
	just need a steering wheel (hence wiimote).

	@uses:  HC-06 BlueTooth Module - communication
	HC-SR04 Sensor - distance sensor
	Andriod phone (Nexus 5x) - steering wheel

 */
//bluetooth connection
const long baudRate           = 115200;
const int rxPin               = 4;      //bluetooth tx pin
const int txPin               = 2;      //bluetooth rx pin
const int bluetoothStatePin   = 11;
//Arcc
const int steeringMotorLeft   = 10; 
const int steeringMotorRight  = 9;  
const int driveMotorForward   = 5;     
const int driveMotorBackward  = 6;     
//HC-SR04
const int echoPin = 8;
const int trigPin = 7;
//bluetooth data
String blueToothVal;
//HC-SR04 safe distance, try to save the car from crashing 
int safeDisitanceInches = 4;
//setting this up allows us to send updates to the
//board without having to remove wires.
SoftwareSerial BlueTooth(rxPin, txPin);
//set up the car
Arcc Arcc(steeringMotorLeft, steeringMotorRight, driveMotorForward, driveMotorBackward);
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

	//HC-SR04
	pinMode(trigPin, OUTPUT);
	pinMode(echoPin, INPUT);

	//open communication
	Serial.begin(baudRate);
	BlueTooth.begin(baudRate);

	Serial.println("Starting: ...");
}

void loop()
{  
	// establish variables for duration of the ping, 
	// and the distance result in inches and centimeters:
	long duration, inches, cm;
	// Read the signal from the sensor: a HIGH pulse whose
	// duration is the time (in microseconds) from the sending
	// of the ping to the reception of its echo off of an object
	// and convert the time into a distance.
	digitalWrite(trigPin, LOW);
	delayMicroseconds(2);
	digitalWrite(trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(trigPin, LOW);
	duration = pulseIn(echoPin, HIGH);
	inches = microsecondsToInches(duration);
	cm = microsecondsToCentimeters(duration);
	// we're connected   
	if (BlueTooth.available())
	{
		blueToothVal = char(BlueTooth.read());
		Serial.print("Captured Char: ");
		Serial.println(blueToothVal);      
	}

	if (blueToothVal == "l") 
	{// left
		Arcc.left(200);
	} 
	else if (blueToothVal == "r") 
	{// right
		Arcc.right(200); 
	}
	else if (blueToothVal == "f") 
	{// forward
		if(inches < safeDisitanceInches) 
		{// NO CHRASHING!
			blueToothVal = "s";
			BlueTooth.print(inches);
			BlueTooth.print("in, ");
			BlueTooth.print(cm);
			BlueTooth.print("cm");
			BlueTooth.println();
			Arcc.allStop();
		} else {
			Arcc.forward(100); 
		}
	}
	else if (blueToothVal == "b") 
	{// backward
		Arcc.backward(200); 
	}
	else if (blueToothVal == "v") 
	{// straight
		Arcc.straight(); 
	}
	else 
	{
		Arcc.allStop();
	}

	//  }
}
/**
 * THX: https://gist.github.com/flakas
 * 
 * According to Parallax's datasheet for the PING))), there are
 * 73.746 microseconds per inch (i.e. sound travels at 1130 feet per
 * second).  This gives the distance travelled by the ping, outbound
 * and return, so we divide by 2 to get the distance of the obstacle.
 * See: http://www.parallax.com/dl/docs/prod/acc/28015-PING-v1.3.pdf
 */
long microsecondsToInches(long microseconds)
{
	return microseconds / 74 / 2;
}
/**
 * THX: https://gist.github.com/flakas
 * 
 * The speed of sound is 340 m/s or 29 microseconds per centimeter.
 * The ping travels out and back, so to find the distance of the
 * object we take half of the distance travelled.
 */
long microsecondsToCentimeters(long microseconds)
{
	return microseconds / 29 / 2;
}

