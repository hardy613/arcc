/*
  Arcc.h - Library for controller a RC Car.
  Created by Scott Hardy, May 15, 2016.
*/
#ifndef Arcc_h
#define Arcc_h

#include "Arduino.h"

class Arcc
{
  public:
    Arcc();
    void powerOn();
    void checkBatteryLife();
    void allStop();
    
  private:
  //bluetooth connection
  int _rxPin;              //bluetooth tx pin
  int _txPin;              //bluetooth rx pin
  int _bluetoothStatePin;  //bluetooth state pin
  long _baudRate;          //AT+BUAD8 ammount of data we can pass
  
  //L293D Connection
  int _steeringMotor1;   //L293D pin 10
  int _steeringMotor2;   //L293D pin 14
  int _driveMotor1;      //L293D pin 2
  int _driveMotor2;      //L293D pin 7
  
  //PING)))
  int _echoPin;
  int _trigPin;
};

#endif
