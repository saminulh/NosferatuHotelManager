#include "stdafx.h"
#include "Utilities.h"

const int Utilities::MORNINGSTARTHOUR = 6;
const int Utilities::MORNINGENDHOUR = 15;
const int Utilities::EVENINGSTARTHOUR = 16;
const int Utilities::EVENINGENDHOUR = 20;
const int Utilities::NIGHTSTARTHOUR = 21;
const int Utilities::NIGHTENDHOUR = 5;

//Master game time
float		Utilities::m_gameTime = 0;
bool		Utilities::m_isGamePaused = false;

//This will be multiplied to calculate the passage of time
float		Utilities::m_currentSpeedFactor = 250*60;

void Utilities::Update() {
	//Don't calculate passage of time if game is paused ... maybe make it go real-time(?)
	if (!m_isGamePaused) {
		//Make change to game time
		float minutesIncreased = screensManager.m_timePerFrame * m_currentSpeedFactor;
		unsigned int hoursIncreased = (int) minutesIncreased / 60;
		minutesIncreased -= 60 * hoursIncreased;
		unsigned int daysIncreased = hoursIncreased / 24;
		hoursIncreased -= 24 * daysIncreased;
		
		m_gameTime = getTimeSum(m_gameTime, daysIncreased * 10000 + hoursIncreased * 100 + minutesIncreased);
	}
}

bool Utilities::isHourInRange(int lowerHourBound, int upperHourBound, int hour) {
	if (lowerHourBound <= upperHourBound) {
		return (hour >= lowerHourBound && hour <= upperHourBound);
	}
	return (hour >= lowerHourBound || hour <= upperHourBound);
}

float Utilities::getTimeSum(float _startTime, float _duration) {
	float finalTime = 0;
	float minutesSum = 0;
	unsigned int hoursSum = 0;
	unsigned int daysSum = 0;

	//Handle minutes first
	minutesSum += (unsigned int)_startTime % 100;
	minutesSum += (unsigned int)_duration % 100;

	hoursSum += (unsigned int)minutesSum / 60;
	minutesSum -= 60 * hoursSum;

	//Handle hours next
	hoursSum += (((unsigned int)_startTime / 100) % 100);
	hoursSum += (((unsigned int)_duration / 100) % 100);

	daysSum += hoursSum / 24;
	hoursSum -= 24 * daysSum;

	daysSum += (unsigned int)_startTime / 10000;
	daysSum += (unsigned int)_duration / 10000;
	//Return as a formatted string
	return daysSum*10000 + hoursSum*100 + minutesSum;
}

float Utilities::getTimeDifference(float _startTime, float _endTime) {
	if (_endTime < _startTime) {
		return -1;
	}

	int startDays = (int)_startTime / 10000;
	int endDays = (int)_endTime / 10000;
	int daysElapsed = endDays - startDays;

	int startHours = ((int)_startTime / 100) % 100;
	int endHours = ((int)_endTime / 100) % 100;
	int hoursElapsed = endHours - startHours;

	float startMinutes = (int)_startTime % 100 + (_startTime - (int)_startTime);
	float endMinutes = (int)_endTime % 100 + (_endTime - (int)_endTime);
	float minutesElapsed = endMinutes - startMinutes;

	std::cout << minutesElapsed << std::endl;
	std::cout << hoursElapsed << std::endl;
	std::cout << daysElapsed << std::endl;

	while (minutesElapsed < 0) {
		hoursElapsed -= 1;
		minutesElapsed += 60;
	}

	while (hoursElapsed < 0) {
		daysElapsed -= 1;
		hoursElapsed += 24;
	}

	return daysElapsed * 10000 + hoursElapsed * 100 + minutesElapsed;
}

int Utilities::randInt(int lowerBound, int upperBound) {
	int range = upperBound - lowerBound + 1;
	return lowerBound + (rand() % range);
}

int Utilities::getCurrentTime() {
	return (int) m_gameTime;
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

	if (isHourInRange(EVENINGSTARTHOUR, EVENINGENDHOUR, getCurrentHour())) {
		phase += 1;
	}

	if (isHourInRange(NIGHTSTARTHOUR, NIGHTENDHOUR, getCurrentHour())) {
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

	if (isHourInRange(EVENINGSTARTHOUR, EVENINGENDHOUR, getHour(time))) {
		phase += 1;
	}

	if (isHourInRange(NIGHTSTARTHOUR, NIGHTENDHOUR, getHour(time))) {
		phase += 2;
	}

	return phase;
}
