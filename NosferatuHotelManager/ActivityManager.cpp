#include "stdafx.h"
#include "ActivityManager.h"
#include "Activity.h"
#include "ActivityRequest.h"
#include "Character/Character.h"
#include "Character/NPC.h"

void ActivityManager::pushNewActivity(Activity activity) {
	activityStack.push_back(activity);
}

void ActivityManager::pushNewRequest(ActivityRequest activityRequest) {
	activityRequestStack.push(activityRequest);

	if (!runningStatus) {
		requestResolutionManager();
	}
}

Activity ActivityManager::getActivityByID(int _characterID) {
	return activityStack[_characterID];
}

int ActivityManager::getActivityStackSize() {
	return activityStack.size();
}

void ActivityManager::requestResolutionManager() {
	while (activityRequestStack.size() > 0) {
		ActivityRequest toBeResolved = activityRequestStack.front();
		activityRequestStack.pop();
		resolveRequest(toBeResolved);
	}
}

void ActivityManager::resolveRequest(ActivityRequest activityRequest){
	Activity activityToBeResolved = activityManager.getActivityByID(activityRequest.getActivityID());
	NPC characterWantingResolution = npcManager.getNPCByID(activityRequest.getRequesterNPCID());
	if (activityRequest.getRequestType() == 0) {											//START
		if (characterWantingResolution.getCurrentActivityID() == -1) return;
		bool fullConfirmation = true;
		for each (int npcToAgreeID in activityToBeResolved.getIDsOfPeopleInvolved()) {
			if (npcToAgreeID != activityRequest.getRequesterNPCID()) {
				NPC npcToAgree = npcManager.getNPCByID(npcToAgreeID);
				npcToAgree.interruptActivity(ActivityRequest(activityRequest.getActivityID(), activityRequest.getRequesterNPCID(), 3));
			}
		}
	}
	else if (activityRequest.getRequestType() == 1) {										//STOP
		///WRAP UP ACTIVITY
		characterWantingResolution.setCurrentActivityID(-1);
	}
}

ActivityManager::ActivityManager() {
	runningStatus = false;
}
