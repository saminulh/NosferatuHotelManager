#pragma once
#include "stdafx.h"


class ActivityOdds {
private:
	int activityID;

	int instantaneousInfluence;
	int* basedOddsVar;
	int baseOddsVarMultiplier;

public:
	ActivityOdds();
	ActivityOdds(int _activityID, int* _baseOddsVar, int _baseOddsVarMultiplier);

	int getTotalOdds();
	void setInstantaneousInfluence(int _instanteousInfluence);
};

