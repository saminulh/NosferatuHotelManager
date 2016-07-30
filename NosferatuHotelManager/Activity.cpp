#include "stdafx.h"
#include "Activity.h"

Activity::Activity(){

}

Activity::Activity(std::string _name, int _npcID, std::vector<int> _IDsOfPeopleInvolved, int _baseOdds, int _executionLowerBound, int _executionUpperBound, bool _useDuration, int _duration, int _endTime){
	activityManager.pushNewActivity(*this);
	activityID = activityManager.getActivityStackSize();

	activityHostID = _npcID;

	IDsOfPeopleInvolved = _IDsOfPeopleInvolved;

	baseOdds = _baseOdds;

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
}
