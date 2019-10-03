// Chessboard.h

#ifndef _CHESSBOARD_h
#define _CHESSBOARD_h

#if defined(ARDUINO) && ARDUINO >= 100
	#include "arduino.h"
#else
	#include "WProgram.h"
#endif

class Chessboard {
public:
	void Init();
private:
};

#endif