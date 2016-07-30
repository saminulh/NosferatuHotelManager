#pragma once
#include "stdafx.h"

class Activity {
public:
	Activity();
	Activity(std::string _name, int _npcID, std::vector<int> _IDsOfPeopleInvolved, int _baseOdds,
		int _executionLowerBound, int _executionUpperBound, bool _useDuration, int _duration, int _endTime);

private:
	int activityID;
	std::string name;

	int activityHostID;
	std::vector<int> IDsOfPeopleInvolved;

	int executionLowerBound;
	int executionUpperBound;
	int startTime;
	int endTime;
	int duration;

	int baseOdds;
	int influenceOnOdds; //Must RESET after each decision
};

