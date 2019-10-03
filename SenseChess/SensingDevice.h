// SensingDevice.h

#ifndef _SENSINGDEVICE_h
#define _SENSINGDEVICE_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class SensingDevice {
public:
	void Init();	// Init
	void Sense();	// Sense: update data
	bool AnyButtonPressed(int* pressedButtonX, int* pressedButtonY);	// Set ints to the longest pressed button if multiple buttons are pressed. Ints only changed if function returns true.

private:
	int** buttonMap;			// 2D-array of how long each button is pressed
	unsigned long lastTime;		// Last time in update
	int** AllocateMemory(unsigned int width, unsigned int height);	// Allocate memory for a 2D-array of ints
	void FreeMemory(int** toFree, unsigned int height);				// Free memory (after using a 2D-array)

	// Constants: sensing device
	const int kButtonsPerRow = 8;			// Buttons per row
	const int kTimePressThreshold = 300;	// How long you should keep your finger on the button to press it [in ms]
	const int kTimeUnpressThreshold = 300;	// How long you should keep your finger off the button to unpress it [in ms] (after you have pressed it kTimePressThreshold + kTimeUnpressThreshold)

	// Constants: i/o pins
	const int kSCLpin = 0;
	const int kSDO0pin = 1;
	const int kSDO1pin = 2;
	const int kSDO2pin = 3;
	const int kSDO3pin = 4;
};

#endif

