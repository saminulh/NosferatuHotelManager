#include "stdafx.h"
#include "ActivityManager.h"
#include "Activity.h"
#include "ActivityRequest.h"

void ActivityManager::pushNewRequest(ActivityRequest activityRequest){
	activityRequestStack.push(activityRequest);

	if (!runningStatus) {
		requestResolutionManager();
	}
}

void ActivityManager::requestResolutionManager() {
	while (activityRequestStack.size() > 0) {
		ActivityRequest toBeResolved = activityRequestStack.front();
		activityRequestStack.pop();
		resolveRequest(toBeResolved);
	}
}

void ActivityManager::resolveRequest(ActivityRequest activityRequest){

}

ActivityManager::ActivityManager() {
	runningStatus = false;
}
