#pragma once
#include "stdafx.h"

class ActivityRequest {
	int activityID;
	int requesterCharacterID;

public:
	ActivityRequest(int actID, int charID, int requestType);
	int getActivityID();
	int getCharacterID();
};

