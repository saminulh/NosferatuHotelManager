#include "stdafx.h"
#include "ActivityRequest.h"


ActivityRequest::ActivityRequest(int actID, int charID, int requestType) {
	activityID = actID;
	requesterCharacterID = charID;
}

int ActivityRequest::getActivityID() {
	return activityID;
}

int ActivityRequest::getCharacterID() {
	return requesterCharacterID;
}
