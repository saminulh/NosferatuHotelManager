#pragma once
#include "stdafx.h"

class DecisionMaker {
private:
	int hostCharacterID;

	std::vector<Activity> activitiesToChooseFrom;
	void selectActivities(std::vector<Activity> activityList);
	void decideActivity();

public:
	DecisionMaker();
	void setHostCharacterID(int _hostCharacterID);
};

