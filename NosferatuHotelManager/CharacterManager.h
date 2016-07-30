#pragma once
#include "stdafx.h"
#include "Character/Character.h"

class CharacterManager {
private:
	std::vector<Character> characterStack;

public:
	void pushNewCharacter(Character character);

	Character getCharacterByID(int characterID);

	int getCharacterStackSize();
};

