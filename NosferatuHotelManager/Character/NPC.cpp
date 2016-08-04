#include "../stdafx.h"
#include "NPC.h"
#include "Character.h"
#include "../DecisionMaker.h"
#include "../Activity.h"

NPC::NPC(std::string type) {
	npcManager.pushNewNPC(*this);
	npcID = npcManager.getNPCStackSize();
	//ADD TRAITS
	currentActivity = nullptr;
	decisionMaker.setHostCharacterID(npcID);
}

int NPC::getNPCID() {
	return npcID;
}

char NPC::getPersonType() {
	return personType;
}

int NPC::getPerceptiveness() {
	return basePerceptiveness;
}

int NPC::getBaseFriendliness() {
	return baseFriendliness;
}

int NPC::getBaseSocialness() {
	return baseSocialness;
}

int NPC::getAggressiveness() {
	return baseAggressiveness;
}

int NPC::getSuspicion() {
	return suspicion;
}

void NPC::setSuspicion(int newSuspicionLevel) {
	suspicion = newSuspicionLevel;
}

std::string NPC::getAge() {
	return age;
}

bool NPC::isMale() {
	return isCharacterMale;
}

int NPC::getFriendlinessTowardsCharacter(int characterID) {
	if (friendlinessModifiers.find(characterID) == friendlinessModifiers.end()) {
		return baseFriendliness;
	}
	return baseFriendliness + friendlinessModifiers[characterID];
}

void NPC::setFriendlinessToCharacter(int characterID, int newFriendliness) {
	friendlinessModifiers[characterID] = newFriendliness - baseFriendliness;
}

Activity* NPC::getCurrentActivity() {
	return currentActivity;
}

void NPC::setCurrentActivity(Activity* _currentActivity) {
	currentActivity = _currentActivity;
}
