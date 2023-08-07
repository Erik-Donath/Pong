#include <stdio.h>
#include <raylib.h>
#include "Defines.h"
#include "Timer.h"
#include "GameState.h"

void GameState::Reset() {
	paused = false;
	timeout.Set(GameTimeoutDelay);
	winner = Winner::None;

	//Generate Random Main Color
	int randomColorNumber = GetRandomValue(0, 10 * 70) % 10;
	printf("[INFO]: Next color is: %i\n", randomColorNumber);
	switch (randomColorNumber) {
	case 0:
		mainColor = BLUE;
		break;
	case 1:
		mainColor = RED;
		break;
	case 2:
		mainColor = GREEN;
		break;
	case 3:
		mainColor = YELLOW;
		break;
	case 4:
		mainColor = { 80, 169, 178, 255 };
		break;
	case 5:
		mainColor = { 255, 102, 0, 255 };
		break;
	case 6:
		mainColor = { 255, 255, 255, 255 };
		break;
	case 7:
		mainColor = { 151, 151, 253, 255 };
		break;
	case 8:
		mainColor = { 204, 51, 255, 255 };
		break;
	case 9:
		mainColor = { 0, 151, 0 };
		break;
	}
}
Color GameState::GetMainColor(int alpha) {
	Color color = mainColor;
	color.a = alpha;
	return color;
}
Color GameState::GetDarkerMainColor(int alpha) {
	Color color = mainColor;
	color.a = alpha; // Darker Color is the half of the main color
	color.r /= 2;
	color.g /= 2;
	color.b /= 2;
	return color;
}
