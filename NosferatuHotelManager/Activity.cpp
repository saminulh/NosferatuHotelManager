#include "stdafx.h"
#include "Activity.h"

Activity::Activity()
{
}

Activity::Activity(std::string _name, int _npcID, std::vector<int> _IDsOfPeopleInvolved, int _baseOdds, int _daysOfActivity, int _executionLowerBound, int _executionUpperBound, bool _useDuration, int _duration, int _endTime, int _variance){
	activityManager.pushNewActivity(*this);
	activityID = activityManager.getActivityStackSize();

	activityHostID = _npcID;

	IDsOfPeopleInvolved = _IDsOfPeopleInvolved;

	baseOdds = _baseOdds;

	daysOfActivity = _daysOfActivity;

	executionLowerBound = _executionLowerBound;
	executionUpperBound = _executionUpperBound;

	if (_useDuration) {
		duration = _duration;
		endTime = -1;
	}
	else {
		duration = -1;
		endTime = _endTime;
	}

	variance = _variance;
}

int Activity::getActivityID() {
	return activityID;
}

std::vector<int> Activity::getIDsOfPeopleInvolved() {
	return IDsOfPeopleInvolved;
}

int Activity::getExecutionLowerBound() {
	return executionLowerBound;
}

int Activity::getExecutionUpperBound() {
	return executionUpperBound;
}

void Activity::setInfluence(int _influence) {
	influenceOnOdds = _influence;
}

int Activity::getTotalOdds() {
	return baseOdds + influenceOnOdds;
}
