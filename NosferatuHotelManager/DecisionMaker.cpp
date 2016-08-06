#include "stdafx.h"
#include "DecisionMaker.h"

void DecisionMaker::selectActivities(std::vector<int> activityIDList) {
	IDsofActivitiesToChooseFrom.clear();
	for each (int activityID in activityIDList) {
		Activity activity = activityManager.getActivityByID(activityID);
		if (Utilities::isHourInRange(activity.getExecutionLowerBound(), activity.getExecutionUpperBound(), Utilities::getCurrentHour())) {
			IDsofActivitiesToChooseFrom.push_back(activityID);
		}
	}
}

void DecisionMaker::decideActivity() {
	
	int totalOdds = 0;

	for each (int activityID in IDsofActivitiesToChooseFrom) {
		Activity activity = activityManager.getActivityByID(activityID);
		totalOdds += npcManager.getNPCByID(hostNPCID).getTotalOddsOfActivity(activityID);
	}

	int stoppingPoint = Utilities::randInt(1,totalOdds);

	std::vector<int>::iterator activityIDIter = IDsofActivitiesToChooseFrom.begin();

	while (stoppingPoint > npcManager.getNPCByID(hostNPCID).getTotalOddsOfActivity(*activityIDIter)) {
		stoppingPoint -= npcManager.getNPCByID(hostNPCID).getTotalOddsOfActivity(*activityIDIter);
		activityIDIter++;
	}

	IDsofActivitiesToChooseFrom.erase(activityIDIter);
	Activity chosenActivity = activityManager.getActivityByID(*activityIDIter);

	activityManager.pushNewRequest(ActivityRequest(chosenActivity.getActivityID(), npcManager.getNPCByID(hostNPCID).getNPCID(), 0));
}

DecisionMaker::DecisionMaker() {

}

void DecisionMaker::setHostNPCID(int _hostNPCID) {
	hostNPCID = _hostNPCID;
}
