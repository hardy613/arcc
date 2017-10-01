#include <SoftwareSerial.h>
//my libraries
#include "Arcc.h"
/**
	@file:  basic set up for blueTooth connection with my phone
	I would like to add a WiiMote in the future
	right now we are just reading the data we send it,
	just need a steering wheel (hence wiimote).

	@uses:  HC-06 Bluetooth Module - communication
	Andriod phone (Nexus 5x) - steering wheel

 */
//bluetooth connection
const long baudRate = 9600;
const int rxPin = 4; //bluetooth tx pin
const int txPin = 2; //bluetooth rx pin
const int bluetoothStatePin = 11;
//Arcc
const int steeringMotorLeft = 10; 
const int steeringMotorRight = 9;  
const int driveMotorForward = 5;     
const int driveMotorBackward = 6;     

//bluetooth data
boolean newData = false;
const byte numChars = 32;
char receivedChars[numChars];
//setting this up allows us to send updates to the
//board without having to remove wires.
SoftwareSerial Bluetooth(rxPin, txPin);
//set up the car
Arcc Arcc(steeringMotorLeft, steeringMotorRight,
		driveMotorForward, driveMotorBackward);
/**
 * Begin our serial and bluetooth buad rates
 * Set the State, RX and TX pins for bluetooth comms
 * Set pins for steering and driving motors
 */
void setup() {
	//bluetooth pins
	pinMode(bluetoothStatePin, INPUT);
	pinMode(rxPin, INPUT);
	pinMode(txPin, OUTPUT);
	//open communication
	Serial.begin(baudRate);
	Bluetooth.begin(baudRate);
	Serial.println("Starting: ...");
}

void loop() {  
	readBluetooth();
	writeData();
	// processData();
	flushData();
}

void readBluetooth() {
	static byte charIndex = 0;
	char ending = '\n';
	char incomingValue;

	while (Bluetooth.available() > 0 && newData == false) {
		incomingValue = Bluetooth.read();

		if(incomingValue != ending) {
			receivedChars[charIndex] = incomingValue;
			charIndex++;
			if (charIndex >= numChars) {
				charIndex = numChars - 1;
			}
		} else {
			receivedChars[charIndex] = '\0'; // terminate the string
			charIndex = 0;
			newData = true;
		}
	}
}

void writeData() {
	if (newData == true) {
		Serial.println(receivedChars);
	}
}

void processData() {
	if (receivedChars == 'l')  {
		Arcc.left(200);
	} else if (receivedChars == 'r') {
		Arcc.right(200); 
	} else if (receivedChars == 'f') {
		Arcc.forward(100); 
	} else if (receivedChars == 'b') {
		Arcc.backward(200); 
	} else if (receivedChars == 'v') {
		Arcc.straight(); 
	} else {
		Arcc.allStop();
	}
}

void flushData() {
	Bluetooth.flush();
	newData = false;
}
