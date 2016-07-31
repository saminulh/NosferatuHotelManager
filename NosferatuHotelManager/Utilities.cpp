#include "stdafx.h"
#include "Utilities.h"

//Master game time
float		Utilities::m_gameTime = 0;
bool		Utilities::m_isGamePaused = false;

//This will be multiplied to calculate the passage of time
float		Utilities::m_currentSpeedFactor = 5;

float Utilities::FormatGameTime(float _time)
{
	if ((unsigned int)_time % 100 > 60)
	{
		//Increment to next hour
		_time += 100;

		//Set the timer back to 0 - CARRY OVER EXTRA TIME!
		_time -= 60;
	}

	if ((unsigned int)_time % 10000 > 2400)
	{
		//Increment to next day
		_time += 10000;

		//Set the hours back to 0 - CARRY OVER EXTRA TIME
		_time -= 2400;
	}

	//Add years? Who knows, who cares?
	return _time;
}

void Utilities::Update()
{
	//Don't calculate passage of time if game is paused ... maybe make it go real-time(?)
	if (!m_isGamePaused)
	{
		//Make change to game time
		m_gameTime += screensManager.m_timePerFrame * m_currentSpeedFactor;
		//Format the number
		FormatGameTime(m_gameTime);
	}
}

float Utilities::getAddedTimes(float _startTime, float _duration)
{
	float finalTime = 0;

	//Handle minutes first
	finalTime += (unsigned int)_startTime % 100;
	finalTime += (unsigned int)_duration % 100;

	//Get the proper format
	//finalTime = FormatGameTime(finalTime);

	//Handle hours next
	finalTime += ((unsigned int)std::floor(_startTime / 100) % 10000) * 100;
	finalTime += ((unsigned int)std::floor(_duration / 100) % 10000) * 100;

	return FormatGameTime(finalTime);
}

float Utilities::getTimeDifference(float _startTime, float _endTime)
{
	return 0.0f;
}

int Utilities::randInt(int lowerBound, int upperBound) {
	return 0;
}

int Utilities::getCurrentTime() {
	return 0;
}

int Utilities::getCurrentDay() {
	return getCurrentTime()/10000;
}

int Utilities::getCurrentHour() {
	return (getCurrentTime() % 10000)/100;
}

int Utilities::getCurrentMinute() {
	return getCurrentTime()%100;
}

int Utilities::getCurrentPhaseOfDay() {
	int phase = 0;

	if (getCurrentDay() % 7 > 4) {
		phase += 3;
	}

	if (getCurrentHour() >= 16) {
		phase += 1;
	}

	if (getCurrentHour() >= 21) {
		phase += 1;
	}

	return phase;
}

int Utilities::getDay(int time) {
	return time / 10000;
}

int Utilities::getHour(int time) {
	return (time % 10000) / 100;
}

int Utilities::getMinute(int time) {
	return time % 100;
}

int Utilities::getPhaseOfDay(int time) {
	int phase = 0;

	if (getDay(time) % 7 > 4) {
		phase += 3;
	}

	if (getHour(time) >= 16) {
		phase += 1;
	}

	if (getHour(time) >= 21) {
		phase += 1;
	}

	return phase;
}
