// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

DebugLogManager debug;

int main()
{
	std::cin.get();

	debug.Start();
	debug.Log(0, "Test!");
	debug.Log(1, "Hello!");
	debug.Log(2, "World!");
	debug.Log(3, "What's Up!");
	debug.Log(4, "Boo!");

    return 0;
}

