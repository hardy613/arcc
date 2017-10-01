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

// Representation is in three bytes, where the first byte is
// the commands, second is the left/right power, and third
// is the forward/backward power.
const char COMMAND_FORWARD =  0b00000001;
const char COMMAND_BACKWARD = 0b00000010;
const char COMMAND_LEFT =     0b00000100;
const char COMMAND_RIGHT =    0b00001000;

const size_t BYTE_COMMAND = 0;
const size_t BYTE_STEERING_POWER = 1;
const size_t BYTE_PROPULSION_POWER = 2;

//setting this up allows us to send updates to the
//board without having to remove wires.
SoftwareSerial Bluetooth(rxPin, txPin);
//set up the car
Arcc arcc = Arcc();

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
  //arrc = Arcc();
	//open communication
	Serial.begin(baudRate);
	Bluetooth.begin(baudRate);
	Serial.println("Starting: ...");
}

void loop() {  
	char bytes[3];
	int index = 0;

	for(int index = 0; Bluetooth.available() > 0 && index < 3; index++) {
		bytes[index] = Bluetooth.read();
		if(index == 2) {
			processData(bytes);
			writeData(bytes);
		}
	}

	Bluetooth.flush();
}

void writeData(const char* const receivedBytes) {
	Serial.println(receivedBytes);
}

void processData(const char* const receivedBytes) {

	if(receivedBytes[BYTE_COMMAND] & COMMAND_LEFT) {
		arcc.left(receivedBytes[BYTE_STEERING_POWER]);
	} else if(receivedBytes[BYTE_COMMAND] & COMMAND_RIGHT) {
		arcc.right(receivedBytes[BYTE_STEERING_POWER]);
	} else {
		arcc.straight();
	}

	if(receivedBytes[BYTE_COMMAND] & COMMAND_FORWARD) {
		arcc.forward(receivedBytes[BYTE_PROPULSION_POWER]);
	} else if(receivedBytes[BYTE_COMMAND] & COMMAND_BACKWARD) {
		arcc.backward(receivedBytes[BYTE_PROPULSION_POWER]);
	} else {
		arcc.stop();
	}
}
