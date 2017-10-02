/*
	 Arcc.h - Library for controller a RC Car.
	 Created by Scott Hardy, May 15, 2016.
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
