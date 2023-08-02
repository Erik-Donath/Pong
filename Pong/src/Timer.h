#pragma once
#include <raylib.h>

struct Timer {
	double start = 0.0;
	double end = 0.0;

	void Set(double seconds) {
		start = GetTime();
		end = start + seconds;
	}
	inline bool InTimeout() {
		return GetTime() < end;
	}
	inline double GetDelay() {
		return end - start;
	}
	inline double InvertedProgress() { // Should return a value from 1 to 0
		return (end - GetTime()) / GetDelay();
	}
	inline double Progress() { // Should return a value from 0 to 1
		return 1.0 - InvertedProgress();
	}
};
