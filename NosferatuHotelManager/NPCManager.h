#pragma once
#include "stdafx.h"
#include "Character/Character.h"

class NPCManager {
private:
	std::vector<NPC> npcStack;

public:
	void pushNewNPC(NPC npc);

	NPC getNPCByID(int npcID);

	int getNPCStackSize();
};

