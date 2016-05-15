/*
  Arcc.cpp - Library for controller a RC Car.
  Created by Scott Hardy, May 15, 2016.
*/
#include "Arduino.h"
#include "Arcc.h"

/**
 * Arcc
 * 
 * @constructor:  The object for our RC car
 */
Arcc::Arcc(int steeringMotorLeft, int steeringMotorRight, int driveMotorForward, int driveMotorBackward)
{
  pinMode(steeringMotorLeft,  OUTPUT);
  pinMode(steeringMotorRight, OUTPUT);
  pinMode(driveMotorForward,  OUTPUT);
  pinMode(driveMotorBackward, OUTPUT);
  
  _steeringMotorLeft  = steeringMotorLeft;   
  _steeringMotorRight = steeringMotorRight;  
  _driveMotorForward  = driveMotorForward;   
  _driveMotorBackward = driveMotorBackward;  
}

/**
 * allStop
 * 
 * set all motor power to 0
 */
void Arcc::allStop()
{
  analogWrite(_steeringMotorLeft,   0);  
  analogWrite(_steeringMotorRight,  0); 
  analogWrite(_driveMotorForward,   0);  
  analogWrite(_driveMotorBackward,  0);
}
/**
 * Directions
 *  left
 *  right
 *  foward
 *  backward
 * @param: {int} power 0 - 255
 */
void Arcc::left(int power)
{
  int output = constrain(power, 0, 255);
  analogWrite(_steeringMotorLeft, output);  
}

void Arcc::right(int power)
{
  int output = constrain(power, 0, 255);
  analogWrite(_steeringMotorRight, output);  
}

void Arcc::forward(int power)
{
  int output = constrain(power, 0, 255);
  analogWrite(_driveMotorForward, output);  
}

void Arcc::backward(int power)
{
  int output = constrain(power, 0, 255);
  analogWrite(_driveMotorBackward, output);  
}

void Arcc::straight()
{
  analogWrite(_steeringMotorLeft,   0); 
  analogWrite(_steeringMotorRight,  0);  
}
/**
 * checkBatteryLife
 * 
 * return the voltage left
 */
void Arcc::checkBatteryLife()
{

}

