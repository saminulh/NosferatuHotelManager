#include "stdafx.h"
#include "Utilities.h"

//Master game time
float		Utilities::m_gameTime = 0;
bool		Utilities::m_isGamePaused = false;

//This will be multiplied to calculate the passage of time
float		Utilities::m_currentSpeedFactor = 5;

void Utilities::FormatGameTime()
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
		m_gameTime += screensManager.m_timePerFrame * m_currentSpeedFactor;
		//Format the number
		FormatGameTime();
	}
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

	if (getCurrentDay() % 7 >= 5) {
		phase += 3;
	}

	if (getCurrentHour() >= EVENINGSTARTHOUR && getCurrentHour() <= EVENINGENDHOUR) {
		phase += 1;
	}

	if (getCurrentHour() >= NIGHTSTARTHOUR || getCurrentHour() <= NIGHTENDHOUR) {
		phase += 2;
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

int Utilities::getAddedTimes(int startTime, int duration) {
	return 0;
}

int Utilities::getTimeDifference(int startTime, int endTime) {
	return 0;
}

