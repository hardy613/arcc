/*
	 Arcc.cpp - Library for controller a RC Car.
*/
#include "Arduino.h"
#include "Arcc.h"
// pins
const int STEERING_MOTOR_LEFT = 10; 
const int STEERING_MOTOR_RIGHT = 9;  
const int DRIVE_MOTOR_FORWARD = 5;     
const int DRIVE_MOTOR_BACKWARD = 6;

/**
 * Arcc
 * 
 * @constructor:  The object for our RC car
 */
Arcc::Arcc() {
	pinMode(STEERING_MOTOR_LEFT,  OUTPUT);
	pinMode(STEERING_MOTOR_RIGHT, OUTPUT);
	pinMode(DRIVE_MOTOR_BACKWARD,  OUTPUT);
	pinMode(DRIVE_MOTOR_FORWARD, OUTPUT);
}

/**
 * Directions
 *  left
 *  right
 *  foward
 *  backward
 * @param: {int} power 0 - 255
 */
void Arcc::left(int power) {
	int output = constrain(power, 0, 255);
	analogWrite(STEERING_MOTOR_RIGHT, 0);  
	analogWrite(STEERING_MOTOR_LEFT, output);  
}

void Arcc::right(int power) {
	int output = constrain(power, 0, 255);
	analogWrite(STEERING_MOTOR_LEFT, 0);  
	analogWrite(STEERING_MOTOR_RIGHT, output);  
}

void Arcc::forward(int power) {
	int output = constrain(power, 0, 255);
	analogWrite(DRIVE_MOTOR_BACKWARD, 0);  
	analogWrite(DRIVE_MOTOR_FORWARD, output);  
}

void Arcc::backward(int power) {
	int output = constrain(power, 0, 255);
	analogWrite(DRIVE_MOTOR_FORWARD, 0);  
	analogWrite(DRIVE_MOTOR_BACKWARD, output);  
}

void Arcc::straight() {
	analogWrite(STEERING_MOTOR_LEFT, 0); 
	analogWrite(STEERING_MOTOR_RIGHT, 0);  
}

void Arcc::stop() {
	analogWrite(DRIVE_MOTOR_FORWARD, 0);
	analogWrite(DRIVE_MOTOR_BACKWARD, 0);
}
