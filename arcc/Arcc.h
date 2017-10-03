/*
	 Arcc.h - Library for controller a RC Car.
*/
#ifndef Arcc_h
#define Arcc_h

#include "Arduino.h"

class Arcc {
	public :
		Arcc();

		void left(int power);
		void right(int power);
		void forward(int power);
		void backward(int power);
		void stop();
		void straight();

};

#endif
