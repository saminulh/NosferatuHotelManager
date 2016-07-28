#include "../stdafx.h"
#include "Character.h"

class NPC : public Character {
	static std::vector<NPC> NPCStack;

	static NPC getNPCByID(int ID) {
		return NPCStack[ID];
	}

	static void createNPC(std::string type) {
		NPC newNPC = NPC();
		//ADD TRAITS
		NPCStack.push_back(newNPC);
	}

	int characterID;
	char personType;

	int basePerceptiveness;
	int baseFriendliness;
	int baseSocialNess;
	int baseAggressiveness;
	int suspicion;
	std::string age;
	bool isMale;

	std::map<Character, int> friendlinessModifiers;


};

