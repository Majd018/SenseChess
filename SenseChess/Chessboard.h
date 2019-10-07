// Chessboard.h

#ifndef _CHESSBOARD_h
#define _CHESSBOARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

enum ChessPiece {
	WhiteKing,
	WhiteQueen,
	WhiteRook,
	WhiteBishop,
	WhiteKnight,
	WhitePawn,
	BlackKing,
	BlackQueen,
	BlackRook,
	BlackBishop,
	BlackKnight,
	BlackPawn,
	Empty
};

class Chessboard {
public:
	void Init();
	ChessPiece DetermineChessPiece(uint8_t row, uint8_t column);		// Determine which chess piece is at a specific cell
private:
	int GetCellReading(uint8_t row, uint8_t column);					// Get the analog reading for a specific cell
	int GetReadingFromMultiplexer(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t multiplexer);	// Get a reading from the multiplexer
	int ConvertCellReadingToResistorValue(int cellReading);				// Convert analog value to resistor value
	bool IsApproximateSameResistor(int resistorReading, int resistor);	// Compare resistor values

	// Pins
	const uint8_t kMultiplexSelectPin0 = 5;
	const uint8_t kMultiplexSelectPin1 = 3;
	const uint8_t kMultiplexSelectPin2 = 4;
	const uint8_t kMultiplexSelectPin3 = 6;
	const uint8_t kMultiplexInputPins[4] = {A3, A4, A5, A6};

	// Resistor values (in kOhm)
	const int kResistorMargin = 10;
	const int kWhiteKingResistance = 500;
	const int kWhiteQueenResistance = 500;
	const int kWhiteRookResistance = 500;
	const int kWhiteBishopResistance = 500;
	const int kWhiteKnightResistance = 500;
	const int kWhitePawnResistance = 500;
	const int kBlackKingResistance = 500;
	const int kBlackQueenResistance = 500;
	const int kBlackRookResistance = 500;
	const int kBlackBishopResistance = 500;
	const int kBlackKnightResistance = 500;
	const int kBlackPawnResistance = 500;
	const int kInvalidReading = -1;
};

#endif