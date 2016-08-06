#include "../stdafx.h"
#include "NPC.h"
#include "Character.h"
#include "../DecisionMaker.h"
#include "../Activity.h"

NPC::NPC(){
}

NPC::NPC(std::string type) {
	npcManager.pushNewNPC(*this);
	npcID = npcManager.getNPCStackSize();
	//ADD TRAITS
	currentActivityID = -1;
	decisionMaker.setHostNPCID(npcID);
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

void NPC::setInfluence(int _activityID, int _influence) {
	activityOdds[_activityID].setInstantaneousInfluence(_influence);
}

void NPC::setInfluence(Activity _activity, int _influence){
	activityOdds[_activity.getActivityID()].setInstantaneousInfluence(_influence);
}

int NPC::getTotalOddsOfActivity(int _activityID) {
	return activityOdds[_activityID].getTotalOdds();
}

int NPC::getTotalOddsOfActivity(Activity _activity) {
	return activityOdds[_activity.getActivityID()].getTotalOdds();
}

int NPC::getCurrentActivityID() {
	return currentActivityID;
}

void NPC::setCurrentActivityID(int _currentActivityID) {
	currentActivityID = _currentActivityID;
}

bool NPC::interruptActivity(ActivityRequest _activityRequest) {





	return false;
}
