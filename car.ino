/*
  Morse.h - Library for flashing Morse code.
  Created by David A. Mellis, November 2, 2007.
  Released into the public domain.
*/
#ifndef Arcc_h
#define Arcc_h

#include "Arduino.h"

//testing classes
class Arcc
{
    private:
      //bluetooth connection
      int _rxPin;             //bluetooth tx pin
      int _txPin;             //bluetooth rx pin
      int _bluetoothStatePin; //bluetooth state pin
      int _baudRate;          //AT+BUAD8 ammount of data we can pass
      
      //L293D Connection
      int _steeringMotor1;//L293D pin 10
      int _steeringMotor2;//L293D pin 14
      int _driveMotor1;   //L293D pin 2
      int _driveMotor2;   //L293D pin 7
      
      //PING)))
      int _echoPin;
      int _trigPin;

    public:
      void powerOn();
      void checkBatteryLife();
      void allStop();
};

void Arcc::powerOn() 
{
  
}

void Arcc::checkBatteryLife()
{
  
}

void Arcc::allStop()
{

}
#endif
