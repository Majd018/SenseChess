// Display.h

#ifndef _DISPLAY_h
#define _DISPLAY_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif
#include <A4988.h>
#include "Chessboard.h"

class Display {
public:
	Display();						// Constructor to initialize the stepper object
	void Init();					// Init stepper
	void Show(ChessPiece piece);	// Display chess piece
private:
	A4988 stepper;					// Stepper object
	int currentPosition;			// Current position of the stepper
	void MoveTo(int newPosition);	// Move to a new position

	// Piece stepper positions (in microsteps (1:16))
	const int kWhiteKingPosition = 1;
	const int kWhiteQueenPosition = 2;
	const int kWhiteRookPosition = 3;
	const int kWhiteBishopPosition = 4;
	const int kWhiteKnightPosition = 5;
	const int kWhitePawnPosition = 6;
	const int kBlackKingPosition = 7;
	const int kBlackQueenPosition = 8;
	const int kBlackRookPosition = 9;
	const int kBlackBishopPosition = 10;
	const int kBlackKnightPosition = 11;
	const int kBlackPawnPosition = 12;
	const int kEmptyCellPosition = 13;

	// Library:
	// https://github.com/laurb9/StepperDriver/blob/master/examples/MicroStepping/MicroStepping.ino
	// https://github.com/laurb9/StepperDriver
	// Stepper setup
	const int kMotorSteps = 200;
	const int kMotorRPM = 12;
	const int kMotorMicrosteps = 16;
	// Pins
	const int kDIRpin = 8;
	const int kSTEPpin = 9;
	const int kSLEEPpin = 13;
	const int kMS1pin = 10;
	const int kMS2pin = 11;
	const int kMS3pin = 12;
};

#endif

