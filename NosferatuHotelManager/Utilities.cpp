#include "stdafx.h"
#include "Utilities.h"

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

