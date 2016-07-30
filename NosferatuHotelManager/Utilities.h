#pragma once
#include "stdafx.h"

class Utilities {
	static void					FormatGameTime();

public:
	//Master game time
	static float				m_gameTime;
	static bool					m_isGamePaused;

	//This will be multiplied to calculate the passage of time
	static float				m_currentSpeedFactor;

	static void					Update();

	static int					randInt(int lowerBound, int upperBound);
	static int					getTime();
	static int					getDay();
	static int					getHour();
	static int					getMinute();
	static int					getPhaseOfDay();
};

