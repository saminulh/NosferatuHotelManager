#pragma once
#include "stdafx.h"

class Utilities {
	static unsigned int	FormatGameTime();

public:
	static void			Update();

	//Master game time
	static float		m_gameTime;
	static bool			m_isGamePaused;

	//This will be multiplied to calculate the passage of time
	static float		m_currentSpeedFactor;

	static int			getTime();
	static int			getDay();
	static int			getHour();
	static int			getMinute();
	static int			getPhaseOfDay();

	static int			randInt(int lowerBound, int upperBound);
};

