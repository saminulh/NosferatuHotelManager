#include "stdafx.h"
#include "CharacterManager.h"
#include "Character/Character.h"

void CharacterManager::pushNewCharacter(Character character) {
	characterStack.push_back(character);
}

Character CharacterManager::getCharacterByID(int characterID) {
	return characterStack[characterID];
}

int CharacterManager::getCharacterStackSize() {
	return characterStack.size();
}
