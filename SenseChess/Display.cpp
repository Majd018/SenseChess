// 
// 
// 

#include "Display.h"

Display::Display() : stepper(kMotorSteps, kDIRpin, kSTEPpin, kSLEEPpin, kMS1pin, kMS2pin, kMS3pin) {}

void Display::Init()
{
	// TODO: how to determine what the starting position of the stepper is? Could use EEPROM or a sensor
	currentPosition = 0;
	stepper.begin(kMotorRPM, kMotorMicrosteps);
	stepper.enable();
}

void Display::Show(ChessPiece piece)
{
	switch (piece)
	{
	case BlackKing:
		MoveTo(kBlackKingPosition);
		break;
	case BlackQueen:
		MoveTo(kBlackQueenPosition);
		break;
	case BlackRook:
		MoveTo(kBlackRookPosition);
		break;
	case BlackBishop:
		MoveTo(kBlackBishopPosition);
		break;
	case BlackKnight:
		MoveTo(kBlackKingPosition);
		break;
	case BlackPawn:
		MoveTo(kBlackPawnPosition);
		break;
	case WhiteKing:
		MoveTo(kWhiteKingPosition);
		break;
	case WhiteQueen:
		MoveTo(kWhiteQueenPosition);
		break;
	case WhiteRook:
		MoveTo(kWhiteRookPosition);
		break;
	case WhiteBishop:
		MoveTo(kWhiteBishopPosition);
		break;
	case WhiteKnight:
		MoveTo(kWhiteKingPosition);
		break;
	case WhitePawn:
		MoveTo(kWhitePawnPosition);
		break;
	case Empty:
		MoveTo(kEmptyCellPosition);
		break;
	}
}

void Display::MoveTo(int newPosition)
{
	int stepsDifferenceFoward = newPosition - currentPosition;										// Calculate difference between two positions
	int stepsDifferenceReverse = -1 * (kMotorSteps * kMotorMicrosteps - stepsDifferenceReverse);	// Get the difference if would rototate backwards
	int moveSteps = min(abs(stepsDifferenceFoward), abs(stepsDifferenceReverse));					// Find the lowest of the two
	stepper.move(moveSteps);		// Move
	currentPosition = newPosition;	// Save the new position
}