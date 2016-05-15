/*
  Arcc.h - Library for controller a RC Car.
  Created by Scott Hardy, May 15, 2016.
*/
#ifndef Arcc_h
#define Arcc_h

#include "Arduino.h"

class Arcc
{
  public :
    Arcc(int steeringMotorLeft, int steeringMotorRight, int driveMotorForward, int driveMotorBackward);
    void checkBatteryLife();
    void allStop();
    void left(int power);
    void right(int power);
    void forward(int power);
    void backward(int power);
    
  private :
  /**
   * variables
   */
  int _steeringMotorLeft;   
  int _steeringMotorRight;  
  int _driveMotorForward;   
  int _driveMotorBackward;
};

#endif
