#include "stdafx.h"
#include "ButtonActions.h"

void ButtonActions::TestButtonAction()
{
	debug.Log(2, "Function pointers work!");
}

void ButtonActions::buttonIsDoor()
{
	editor.GetCurrentTileProperties().m_isDoor = !editor.GetCurrentTileProperties().m_isDoor;
}
