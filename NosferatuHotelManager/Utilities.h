#pragma once
#include "stdafx.h"

class Utilities {
	static float				FormatGameTime(float _time);

public:
	//Master game time
	static float				m_gameTime;
	static bool					m_isGamePaused;

	//This will be multiplied to calculate the passage of time
	static float				m_currentSpeedFactor;

	static void					Update();


	static int					getCurrentTime();
	static int					getCurrentDay();
	static int					getCurrentHour();
	static int					getCurrentMinute();
	static int					getCurrentPhaseOfDay();

	static int					getDay(int time);
	static int					getHour(int time);
	static int					getMinute(int time);
	static int					getPhaseOfDay(int time);

	static float				getAddedTimes(float _startTime, float _duration);
	static float				getTimeDifference(float _startTime, float _endTime);

	static int					randInt(int lowerBound, int upperBound);

};

