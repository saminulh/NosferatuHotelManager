#include "stdafx.h"
#include "ActivityOdds.h"


ActivityOdds::ActivityOdds()
{
}

ActivityOdds::ActivityOdds(int _activityID, int * _baseOddsVar, int _baseOddsVarMultiplier) {
	activityID = _activityID;
	basedOddsVar = _baseOddsVar;
	baseOddsVarMultiplier = _baseOddsVarMultiplier;
	instantaneousInfluence = 0;
}

int ActivityOdds::getTotalOdds() {
	return instantaneousInfluence + (baseOddsVarMultiplier * (*basedOddsVar));
}

void ActivityOdds::setInstantaneousInfluence(int _instanteousInfluence){
	instantaneousInfluence = _instanteousInfluence;
}