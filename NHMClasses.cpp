// ConsoleApplication2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <time.h>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

int randInt(int start, int end) {
	int range = end - start + 1;
	int randomNumber = start + (rand() % range);
	
	return randomNumber;
}

class Character{
	double walkingSpeed;
	double runningSpeed;
};

class Vampire : public Character {

};

class Helper : public Character {

};

class NPC : public Character {
	static vector<NPC> NPCMap;
	
	static NPC getNPCByID(int ID) {
		return NPCMap[ID];
	}
	
	static void createNPC(string type) {

	}

	int characterID;
	char personType;

	int basePerceptiveness;
	int baseFriendliness;
	int baseSocialNess;
	int baseAggressiveness;
	int suspicion;
	string age;
	bool isMale;

	map<int, int> friendlinessModifiers;
	
	
};

class Activity {
	char timeOfDay;
	int endTime;
	int numberOfPeople;
	string personTypes;

	static create

};

class Room {

};

class Tile {


};


int main()
{
	srand(time(NULL));
	cout << randInt(8,100) << endl;
	cout << randInt(8, 100) << endl;
	cout << randInt(8, 100) << endl;
	system("PAUSE");
    return 0;
}

