#include "stdafx.h"
#include "DecisionMaker.h"

void DecisionMaker::selectActivities(std::vector<Activity> activityList) {
	activitiesToChooseFrom.clear();
	for (std::vector<Activity>::iterator iter = activityList.begin(); iter < activityList.end(); iter++) {
		if (Utilities::isHourInRange((*iter).getExecutionLowerBound(), (*iter).getExecutionUpperBound(), Utilities::getCurrentHour())) {
			activitiesToChooseFrom.push_back(*iter);
		}
	}
}

void DecisionMaker::decideActivity() {
	std::vector<Activity>::iterator iter;
	
	int totalOdds = 0;

	for (iter = activitiesToChooseFrom.begin(); iter < activitiesToChooseFrom.end(); iter++) {
		totalOdds += (*iter).getTotalOdds();
	}

	int stoppingPoint = Utilities::randInt(1,totalOdds);

	iter = activitiesToChooseFrom.begin();

	while (stoppingPoint > (*iter).getTotalOdds()) {
		stoppingPoint -= (*iter).getTotalOdds();
		iter++;
	}

	Activity chosenActivity = (*iter);

	activityManager.pushNewRequest(ActivityRequest(chosenActivity.getActivityID(), hostCharacterID, 0));

}

DecisionMaker::DecisionMaker() {

}

void DecisionMaker::setHostCharacterID(int _hostCharacterID) {
	hostCharacterID = _hostCharacterID;
}
