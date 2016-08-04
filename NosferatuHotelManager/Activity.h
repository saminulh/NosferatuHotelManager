#pragma once
#include "stdafx.h"

class Activity {
public:
	Activity();
	Activity(std::string _name, int _npcID, std::vector<int> _IDsOfPeopleInvolved, int _baseOdds,
		int _daysOfActivity, int _executionLowerBound, int _executionUpperBound, bool _useDuration,
		int _duration, int _endTime, int _variance);

	int getActivityID();

	std::vector<int> getIDsOfPeopleInvolved();

	int getExecutionLowerBound();
	int getExecutionUpperBound();

	void setInfluence(int _influence);
	int getTotalOdds();

private:
	int activityID;
	std::string name;

	int activityHostID;
	std::vector<int> IDsOfPeopleInvolved;

	int daysOfActivity; //0 = weekdays, 1 = weekends, 2 = both

	int executionLowerBound;
	int executionUpperBound;
	int startTime;
	int endTime;
	int duration;
	int variance;

	int baseOdds;
	int influenceOnOdds; //Must RESET after each decision
};

