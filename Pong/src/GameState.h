#pragma once

#include <raylib.h>
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
public:
	void Reset();
	Color GetMainColor(int alpha);
	Color GetDarkerMainColor(int alpha = 255);

	inline void  Pause() {
		paused = !paused;
	}
	inline Color GetMainColor() {
		return mainColor;
	}
};
