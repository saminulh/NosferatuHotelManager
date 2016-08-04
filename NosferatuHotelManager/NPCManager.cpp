#include "stdafx.h"
#include "NPCManager.h"
#include "Character/Character.h"

void NPCManager::pushNewNPC(NPC npc) {
	npcStack.push_back(npc);
}

NPC NPCManager::getNPCByID(int npcID) {
	return npcStack[npcID];
}

int NPCManager::getNPCStackSize() {
	return npcStack.size();
}
