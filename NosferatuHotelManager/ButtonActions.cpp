#include "stdafx.h"
#include "ButtonActions.h"

void ButtonActions::TestButtonAction()
{
	debug.Log(2, "Function pointers work!");
}

void ButtonActions::buttonIsDoor()
{
	editor.GetCurrentTileProperties().m_isDoor = !editor.GetCurrentTileProperties().m_isDoor;
	if (editor.GetCurrentTileProperties().m_isDoor)
		debug.Log(1, "Door set to true");
	else
		debug.Log(1, "Door set to false");
}

void ButtonActions::buttonIsRoomExit()
{
	editor.GetCurrentTileProperties().m_isRoomExit = !editor.GetCurrentTileProperties().m_isRoomExit;
	if (editor.GetCurrentTileProperties().m_isRoomExit)
		debug.Log(1, "Room exit set to true");
	else
		debug.Log(1, "Room exit set to false");
}
