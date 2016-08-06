#pragma once
#include "../stdafx.h"
#include "Character.h"
#include "../DecisionMaker.h"
#include "../Activity.h"
#include "../ActivityOdds.h"

class NPC : public Character {
private:
	int								npcID;

	char							personType;
	int								basePerceptiveness;
	int								baseFriendliness;
	int								baseSocialness;
	int								baseAggressiveness;
	int								suspicion;
	std::string						age;
	bool							isCharacterMale;

	std::map<int, int>				friendlinessModifiers;

	std::vector<int>				activityIDsByPhaseOfDay;
	int								currentActivityID;

	std::map<int, ActivityOdds>		activityOdds;

	DecisionMaker					decisionMaker;

public:
	NPC();
	NPC(std::string type);

	int								getNPCID();
	char							getPersonType();
	int								getPerceptiveness();
	int								getBaseFriendliness();
	int								getBaseSocialness();
	int								getAggressiveness();
	int								getSuspicion();
	void							setSuspicion(int newSuspicionLevel);
	std::string						getAge();
	bool							isMale();

	int								getFriendlinessTowardsCharacter(int characterID);
	void							setFriendlinessToCharacter(int characterID, int newFriendliness);

	void							setInfluence(int _activityID, int _influence);
	void							setInfluence(Activity _activity, int _influence);

	int								getTotalOddsOfActivity(int _activityID);
	int								getTotalOddsOfActivity(Activity _activity);

	int								getCurrentActivityID();
	void							setCurrentActivityID(int _currentActivityID);

	bool							interruptActivity(ActivityRequest _activityRequest);

};

