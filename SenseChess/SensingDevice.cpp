// 
// 
// 

#include "SensingDevice.h"
void SensingDevice::Init()
{
	// Allocate and prepare
	buttonMap = AllocateMemory(kButtonsPerRow, kButtonsPerRow);	
	lastTime = millis();
}

void SensingDevice::Sense()
{
	int** inputMap = AllocateMemory(kButtonsPerRow, kButtonsPerRow);

	// Read input, credits to Majd
	for (byte i = 0; i < 16; i++)
	{
		byte rIdx = i / 4; // Row index
		byte cIdx = i % 4; // Column index

		digitalWrite(kSCLpin, HIGH);

		inputMap[rIdx][cIdx] = digitalRead(kSDO0pin);
		inputMap[rIdx][cIdx + 4] = digitalRead(kSDO1pin);
		inputMap[7 - rIdx][3 - cIdx] = digitalRead(kSDO2pin);
		inputMap[7 - rIdx][7 - cIdx] = digitalRead(kSDO3pin);

		digitalWrite(kSCLpin, LOW);

		delayMicroseconds(5);
	}
	delay(3);	// TODO: use a clock to determine this delay

	// Now, update time information about how long each button has been pressed
	unsigned long currentTime = millis();				// Get current time
	unsigned long deltaTime = currentTime - lastTime;	// Calculate time difference
	lastTime = currentTime;

	for (int i = 0; i < kButtonsPerRow; i++) 
	{
		for (int j = 0; j < kButtonsPerRow; j++)
		{
			if (inputMap[i][j] == 1)
			{
				buttonMap[i][j] = buttonMap[i][j] + deltaTime;		// Increase by time difference, can go to infinity, but will take 25 days to reach the int max
			}
			else if (inputMap[i][j] == 0 && buttonMap[i][j] > 0)	// Not pressed at the moment, but was pressed in the not so long past
			{
				if (buttonMap[i][j] > (kTimePressThreshold + kTimeUnpressThreshold))	
				{
					buttonMap[i][j] = kTimePressThreshold + kTimeUnpressThreshold;		// Set to the threshold if we are over it, so we can estimate how long we should keep the button pressed in the system
				}

				// Decrease time
				if (deltaTime < buttonMap[i][j])
				{
					buttonMap[i][j] = buttonMap[i][j] - deltaTime;	// Decrease by time difference
				}
				else 
				{
					buttonMap[i][j] = 0;
				}
			}
		}
	}

	// Free memory
	FreeMemory(inputMap, kButtonsPerRow);
}

bool SensingDevice::AnyButtonPressed(int* pressedButtonX, int* pressedButtonY)
{
	int maxPressTime = 0;
	for (int i = 0; i < kButtonsPerRow; i++)
	{
		for (int j = 0; j < kButtonsPerRow; j++)
		{
			if (buttonMap[i][j] > kTimePressThreshold && buttonMap[i][j] > maxPressTime)
			{
				maxPressTime = buttonMap[i][j];
				*pressedButtonX = i;
				*pressedButtonY = j;
			}
		}
	}
	if (maxPressTime > 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int** SensingDevice::AllocateMemory(unsigned int width, unsigned int height) 
{
	int** map = 0;
	map = new int*[height];

	for (int i = 0; i < height; i++)
	{
		map[i] = new int[width];
		for (int j = 0; j < width; j++)
		{
			map[i][j] = 0;
		}
	}
	return map;
}

void SensingDevice::FreeMemory(int** toFree, unsigned int height) 
{
	for (int h = 0; h < height; h++)
	{
		delete[] toFree[h];
	}
	delete[] toFree;
}