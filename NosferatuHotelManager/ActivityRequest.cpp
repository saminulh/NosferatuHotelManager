#include "stdafx.h"
#include "ActivityRequest.h"


ActivityRequest::ActivityRequest(int actID, int _requesterCharacterID, int _requesteeCharacterID, int _requestType) {
	activityID = actID;
	requesterCharacterID = _requesterCharacterID;
	requesterCharacterID = _requesteeCharacterID;
	requestType = _requestType;
}

int ActivityRequest::getActivityID() {
	return activityID;
}

int ActivityRequest::getRequesterNPCID() {
	return requesterCharacterID;
}

int ActivityRequest::getRequesteeNPCID() {
	return requesteeCharacterID;
}

int ActivityRequest::getRequestType() {
	return requestType;
}
