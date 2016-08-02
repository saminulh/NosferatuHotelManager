#pragma once
#include "stdafx.h"

class Utilities {
public:
	//Master game time
	//Formatted as [Day][Hour][Minute]
	//Hour and minute both occupy exactly two digits each
	//Day occupies all other leading digits
	static float				m_gameTime;
	static bool					m_isGamePaused;

	//This will be multiplied to calculate the passage of time
	static float				m_currentSpeedFactor;

	static void					Update();

	static bool					isHourInRange(int lowerHourBound, int upperHourBound, int hour);

	static int					getCurrentTime();
	static int					getCurrentDay();
	static int					getCurrentHour();
	static int					getCurrentMinute();
	static int					getCurrentPhaseOfDay();

	static int					getDay(int time);
	static int					getHour(int time);
	static int					getMinute(int time);
	static int					getPhaseOfDay(int time);

	static float				FormatGameTime(float _time);

	//Takes in two formatted game time floats and returns their sum in game time
	static float				getTimeSum(float _startTime, float _duration);
	//Takes in two formatted game time floats and returns their difference in game time
	static float				getTimeDifference(float _startTime, float _endTime);

	static int					randInt(int lowerBound, int upperBound);

	static float				getFPS(const sf::Time& _time);
};

