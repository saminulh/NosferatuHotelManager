#pragma once

//This class will be the primary (only?) container for button on-click events
class ButtonActions
{
public:
	static void TestButtonAction();
	static void	buttonIsDoor();
	static void	buttonIsRoomExit();
	static void	buttonIsSolid();
	static void	buttonSearchForAnims();

	static void	buttonUpInAnims();
	static void	buttonDownInAnims();

	static void	buttonSaveMap();

	static void	buttonFileNameField();
	static void	createMapButton();
	static void	loadMapButton();
};