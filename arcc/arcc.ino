#include <SoftwareSerial.h>
//my libraries
#include "Arcc.h"
/**
	@file:  basic set up for blueTooth connection with my phone
	I would like to add a WiiMote in the future
	right now we are just reading the data we send it,
	just need a steering wheel (hence wiimote).

	@uses:  HC-06 BlueTooth Module - communication
	Andriod phone (Nexus 5x) - steering wheel

 */
//bluetooth connection
const long baudRate           = 9600;
const int rxPin               = 4;      //bluetooth tx pin
const int txPin               = 2;      //bluetooth rx pin
const int bluetoothStatePin   = 11;
//Arcc
const int steeringMotorLeft   = 10; 
const int steeringMotorRight  = 9;  
const int driveMotorForward   = 5;     
const int driveMotorBackward  = 6;     

//bluetooth data
char incomingValue;
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
	//open communication
	Serial.begin(baudRate);
	BlueTooth.begin(baudRate);
	Serial.println("Starting: ...");
}

void loop() {  
	// we're connected   
	if (BlueTooth.available()) {
		incomingValue = char(BlueTooth.read());
		Serial.print("Captured Char: ");
		Serial.println(incomingValue);      
	} else if (Serial.available() > 0) {
		incomingValue = char(Serial.read());
		Serial.print("Captured Char: ");
		Serial.println(incomingValue);
	}

	if (incomingValue == 'l')  {// left
		Arcc.left(200);
	} else if (incomingValue == 'r') {// right
		Arcc.right(200); 
	} else if (incomingValue == 'f') {// forward
		Arcc.forward(100); 
	} else if (incomingValue == 'b') {// backward
		Arcc.backward(200); 
	} else if (incomingValue == 'v') {// straight
		Arcc.straight(); 
	} else {
		Arcc.allStop();
	}
}
