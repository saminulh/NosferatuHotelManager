#include "../stdafx.h"
#include "Character.h"

class NPC : public Character {
	static std::vector<NPC> NPCStack;

	static NPC getNPCByID(int ID);
	static void createNPC(std::string type);

private:
	char personType;
	int basePerceptiveness;
	int baseFriendliness;
	int baseSocialNess;
	int baseAggressiveness;
	int suspicion;
	std::string age;
	bool isMale;

	std::map<Character, int> friendlinessModifiers;

public:
	char getPersonType();
	int getPerceptiveness();
	int getBaseFriendliness();
	int getBaseSocialNess();
	int getAggressiveness();
	int getSuspicion();
	void setSuspicion(int newSuspicionLevel);
	std::string getAge();
	bool isMale();

	int getFriendlinessToCharacter(Character character);
	void setFriendlinessToCharacter(Character character, int newFriendliness);

};

