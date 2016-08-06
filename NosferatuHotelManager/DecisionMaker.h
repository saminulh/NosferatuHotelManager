#pragma once
#include "stdafx.h"

class DecisionMaker {
private:
	int hostNPCID;

	std::vector<int> IDsofActivitiesToChooseFrom;
	void selectActivities(std::vector<int> activityIDList);
	void decideActivity();

public:
	DecisionMaker();
	void setHostNPCID(int _hostNPCID);
};

