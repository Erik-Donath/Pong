#pragma once

#include <raylib.h>
#include "Defines.h"
#include "Timer.h"

enum Winner : unsigned char {
	None = 0,
	Left = 1,
	Right = 2
};

// Must be intilazed after raylib!
struct GameState {
private:
	Color mainColor = RAYWHITE;

public:
	bool paused = false;
	Timer timeout;
	Winner winner = Winner::None;

	void Reset() {
		paused = false;
		timeout.Set(GameTimeoutDelay);
		winner = Winner::None;

		//Generate Random Main Color
		int randomColorNumber = GetRandomValue(0, 5 * 70) % 5;
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
		default:
			mainColor = RAYWHITE;
			break;
		}
	}
	inline void  Pause() {
		paused = !paused;
	}
	inline Color GetMainColor() {
		return mainColor;
	}
	inline Color GetMainColor(int alpha) {
		Color color = mainColor;
		color.a = alpha;
		return color;
	}
	inline Color GetDarkerMainColor(int alpha = 255) {
		Color color = mainColor;
		color.a = alpha; // Darker Color is the half of the main color
		color.r /= 2;
		color.g /= 2;
		color.b /= 2;
		return color;
	}
};
