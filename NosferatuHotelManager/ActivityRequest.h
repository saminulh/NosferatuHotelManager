#pragma once
#include "stdafx.h"

class ActivityRequest {
	int activityID;
	int requesterCharacterID;
	int requesteeCharacterID;
	int requestType;

public:
	ActivityRequest(int actID, int _requesterNPCID, int _requestType);
	int getActivityID();
	int getRequesterNPCID();
	int getRequesteeNPCID();
	int getRequestType();
};

