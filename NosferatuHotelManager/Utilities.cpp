#include "stdafx.h"
#include "Utilities.h"

unsigned int Utilities::FormatGameTime()
{
	if ((unsigned int)m_gameTime / 100 > 60)
	{
		//Increment to next hour
		m_gameTime += 100;

		//Set the timer back to 0
		m_gameTime -= (unsigned int)m_gameTime % 100;
	}

	if ((unsigned int)m_gameTime / 10000 > 24000)
	{
		//Increment to next day
		m_gameTime += 100000;

		//Set the hours back to 0
		m_gameTime -= (unsigned int)m_gameTime % 10000;
	}

	//Add years? Who knows, who cares?
}

void Utilities::Update()
{
	//Don't calculate passage of time if game is paused ... maybe make it go real-time(?)
	if (!m_isGamePaused)
	{
		//Make change to game time
		m_gameTime = screensManager.m_timePerFrame * m_currentSpeedFactor;
		//Format the number
		FormatGameTime();
	}
}

int Utilities::randInt(int lowerBound, int upperBound) {
	return 0;
}

int Utilities::getTime() {
	return 0;
}

int Utilities::getDay() {
	return getTime()/10000;
}

int Utilities::getHour() {
	return (getTime() % 10000)/100;
}

int Utilities::getMinute() {
	return getTime()%100;
}

int Utilities::getPhaseOfDay() {
	int phase = 0;

	if (getDay() % 7 > 4) {
		phase += 3;
	}

	if (getHour() >= 16) {
		phase += 1;
	}

	if (getHour() >= 21) {
		phase += 1;
	}
	return phase;
}

