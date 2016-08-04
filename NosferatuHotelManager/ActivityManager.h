#pragma once
#include "stdafx.h"
#include "Activity.h"
#include "ActivityRequest.h"
#include "Character/Character.h"
#include "Character/NPC.h"

class ActivityManager {
private:
	bool runningStatus;
	std::vector<Activity> activityStack;
	std::queue<ActivityRequest> activityRequestStack;

	void requestResolutionManager();
	void resolveRequest(ActivityRequest activityRequest);


public:
	ActivityManager();

	void pushNewActivity(Activity activity);
	void pushNewRequest(ActivityRequest activityRequest);

	Activity getActivityByID(int _characterID);

	int getActivityStackSize();
};

