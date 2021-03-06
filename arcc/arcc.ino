#include <SoftwareSerial.h>
//my libraries
#include "Arcc.h"
//bluetooth connection
const long baudRate = 9600;
const int rxPin = 4; //bluetooth tx pin
const int txPin = 2; //bluetooth rx pin
const int bluetoothStatePin = 11;

// Representation is in three bytes, where the first byte is
// the commands, second is the left/right power, and third
// is the forward/backward power.
const char COMMAND_FORWARD = 0b00000001;
const char COMMAND_BACKWARD = 0b00000010;
const char COMMAND_LEFT = 0b00000100;
const char COMMAND_RIGHT = 0b00001000;
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
	//open communication
	Serial.begin(baudRate);
	Bluetooth.begin(baudRate);
	Serial.println("Starting: ...");
}

void loop() {
  if(Bluetooth.available() > 0) {
  	unsigned char bytes[3];
  	int index = 0;
    if (Bluetooth.readBytes(bytes, 3) == 3) {
      processData(bytes);
    }
    writeData(bytes);
  }
	Bluetooth.flush();
}

void writeData(const unsigned char* const receivedBytes) {
  Serial.print("receivedBytes: ");
  for(int index = 0; index < 3; index++) {
    Serial.print(receivedBytes[index], BIN);
    Serial.print(", ");
  }
	Serial.println("");
}

void processData(const unsigned char* const receivedBytes) {

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
