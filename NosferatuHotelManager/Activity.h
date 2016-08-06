#pragma once
#include "stdafx.h"

class Activity {
public:
	Activity();
	Activity(std::string _name, std::vector<int> _IDsOfPeopleInvolved,
		int _daysOfActivity, int _executionLowerBound, int _executionUpperBound, bool _useDuration,
		int _duration, int _endTime, int _variance);

	int getActivityID();

	std::vector<int> getIDsOfPeopleInvolved();

	int getExecutionLowerBound();
	int getExecutionUpperBound();

private:
	int activityID;
	std::string name;
	std::vector<int> IDsOfPeopleInvolved;

	int daysOfActivity; //0 = weekdays, 1 = weekends, 2 = both

	int executionLowerBound;
	int executionUpperBound;
	int startTime;
	int endTime;
	int duration;
	int variance;
};

