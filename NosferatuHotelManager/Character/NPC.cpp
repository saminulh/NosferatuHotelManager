#include "../stdafx.h"
#include "NPC.h"
#include "Character.h"

NPC NPC::getNPCByID(int ID) {
	return NPCStack[ID];
}

void NPC::createNPC(std::string type) {
	NPC newNPC = NPC();
	//ADD TRAITS
	NPCStack.push_back(newNPC);
}

char NPC::getPersonType() {
	return personType;
}

int NPC::getPerceptiveness()
{
	return basePerceptiveness;
}

int NPC::getBaseFriendliness()
{
	return 0;
}

int NPC::getBaseSocialNess()
{
	return baseFriendliness;
}

int NPC::getAggressiveness()
{
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
	return isMale;
}

int NPC::getFriendlinessToCharacter(Character character) {
	return baseFriendliness+friendlinessModifiers[character];
}

void NPC::setFriendlinessToCharacter(Character character, int newFriendliness) {
	friendlinessModifiers[character] = newFriendliness - getBaseFriendliness();
}
