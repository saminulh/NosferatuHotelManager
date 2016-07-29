#include "stdafx.h"
#include "Activity.h"
#include "ActivityRequest.h"

class ActivityManager {
private:
	bool runningStatus;
	std::vector<Activity> activityStack;
	std::queue<ActivityRequest> activityRequestStack;

	void pushNewRequest(ActivityRequest activityRequest);
	void requestResolutionManager();
	void resolveRequest(ActivityRequest activityRequest);


public:
	ActivityManager();
};

