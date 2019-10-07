// 
// 
// 

#include "Chessboard.h"

void Chessboard::Init() 
{
	// Can be removed if not used
}

ChessPiece Chessboard::DetermineChessPiece(uint8_t row, uint8_t column)
{
	int cellReading = GetCellReading(row, column);						// Get analog input of cell
	int resistorValue = ConvertCellReadingToResistorValue(cellReading);	// Convert cell value to resistor value

	if (IsApproximateSameResistor(resistorValue, kBlackKingResistance))	// Find piece corresponding to resistor value
	{
		return BlackKing;
	}
	else if (IsApproximateSameResistor(resistorValue, kBlackQueenResistance))
	{
		return BlackQueen;
	}
	else if (IsApproximateSameResistor(resistorValue, kBlackRookResistance))
	{
		return BlackRook;
	}
	else if (IsApproximateSameResistor(resistorValue, kBlackBishopResistance))
	{
		return BlackBishop;
	}
	else if (IsApproximateSameResistor(resistorValue, kBlackKnightResistance))
	{
		return BlackKnight;
	}
	else if (IsApproximateSameResistor(resistorValue, kBlackPawnResistance))
	{
		return BlackPawn;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhiteKingResistance))
	{
		return WhiteKing;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhiteQueenResistance))
	{
		return WhiteQueen;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhiteRookResistance))
	{
		return WhiteRook;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhiteBishopResistance))
	{
		return WhiteBishop;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhiteKnightResistance))
	{
		return WhiteKnight;
	}
	else if (IsApproximateSameResistor(resistorValue, kWhitePawnResistance))
	{
		return WhitePawn;
	}
	else 
	{
		return Empty;	// If we don't understand which piece it is, assume it is empty (TODO: maybe something different here, e.g. something to warn the user)
	}
}

bool Chessboard::IsApproximateSameResistor(int resistorReading, int resistor)
{
	if (resistorReading > (resistor - kResistorMargin) && resistorReading < (resistor + kResistorMargin))
	{
		return true;
	}
	else 
	{
		return false;
	}
}

int Chessboard::ConvertCellReadingToResistorValue(int cellReading)
{
	const double v_in = 5.0;
	double v_out = cellReading * (5.0 / 1023.0);	// v_analog_input (v_out) = analog_input * (5.0 / 1023.0);

	// TODO: depends on setup of voltage divider (v_out = (v_s*R2) / (R1+R2)), do we need to calculate R1 or R2?
	// R1 = R2 * ((v_in / v_out) - 1)
	// R2 = R1 * (1 / ((v_in / v_out) - 1))

}

int Chessboard::GetCellReading(uint8_t row, uint8_t column)
{
	uint8_t multiplexer = floor(row / 2);	// Find the id of the multiplexer (rows 0-1: 0, rows 2-3: 1, rows 4-5: 2, rows 6-7: 3)
	if (multiplexer >= 0 && multiplexer <= 3)
	{
		uint8_t selectorValues[4];
		// 1->3rd bit: bit representation of the column
		for (uint8_t i = 0; i < 3; i++) {
			uint8_t state = bitRead(column, i);
			selectorValues[i] = state;
		}
		// 4th bit: 
		// 0->7: row 0
		// 8->15: row 1
		selectorValues[3] = row - (multiplexer * 2);
		return GetReadingFromMultiplexer(selectorValues[0], selectorValues[1], selectorValues[2], selectorValues[3], multiplexer);
	}
	else
	{
		return kInvalidReading;
	}
}

int Chessboard::GetReadingFromMultiplexer(uint8_t s0, uint8_t s1, uint8_t s2, uint8_t s3, uint8_t multiplexer)
{
	digitalWrite(kMultiplexSelectPin0, s0);	// TODO: order could be different --> datasheet
	digitalWrite(kMultiplexSelectPin1, s1);
	digitalWrite(kMultiplexSelectPin2, s2);
	digitalWrite(kMultiplexSelectPin3, s3);
	// TODO: do we need any delay here? --> datasheet
	return analogRead(kMultiplexInputPins[multiplexer]);
}
