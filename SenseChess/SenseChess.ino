// the setup function runs once when you press reset or power the board
#include <A4988.h>
#include "SensingDevice.h"
#include "Display.h"
#include "Chessboard.h"

#pragma region Constants
const unsigned long SERIAL_RATE = 38400;	// Serial communiciation bit 38400
#pragma endregion

#pragma region Objects
SensingDevice sensingDevice;
Display display;
Chessboard chessboard;
#pragma endregion



void setup() {
	Serial.begin(SERIAL_RATE);	// Init serial
	delay(1000);
	Serial.println("[INFO] Starting SenseChess...");
	sensingDevice.Init();
	display.Init();
}

void loop() {
	sensingDevice.Sense();

	int buttonX;
	int buttonY;
	bool anyButtonPressed = sensingDevice.AnyButtonPressed(&buttonX, &buttonY);
	if (anyButtonPressed)
	{
		Serial.print("Pressed: ");
		Serial.print(buttonX);
		Serial.print(",");
		Serial.println(buttonY);

		ChessPiece piece = chessboard.DetermineChessPiece(buttonX, buttonY);
		display.Show(piece);
	}
}
