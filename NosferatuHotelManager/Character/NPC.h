#pragma once
#include "../stdafx.h"
#include "Character.h"
#include "../DecisionMaker.h"
#include "../Activity.h"

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

	std::vector<Activity>			activitiesByPhaseOfDay;
	Activity*						currentActivity;

	DecisionMaker					decisionMaker;

public:
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

	Activity*						getCurrentActivity();
	void							setCurrentActivity(Activity* _currentActivity);

};

