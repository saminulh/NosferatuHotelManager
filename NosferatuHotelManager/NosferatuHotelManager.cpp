// NosferatuHotelManager.cpp : Defines the entry point for the console application.
//


/**********************************************************************************/
/*
**					MAP EDITOR - NOT THE ACTUAL GAME
**
/**********************************************************************************/

#include "stdafx.h"
#include "AnimationClass.h"

#include "Button.h"
#include "ButtonActions.h"

#include "Utilities.h"

DebugLogManager		debug;
GraphicsManager		graphicsManager;
AudioManager		audioManager;
ScreensManager		screensManager;
GUIManager			guiManager;
ActivityManager		activityManager;
CharacterManager	characterManager;
Editor				editor;
UserInputManager	userInputManager;

const int MORNINGSTARTHOUR = 6;
const int MORNINGENDHOUR = 15;
const int EVENINGSTARTHOUR = 16;
const int EVENINGENDHOUR = 20;
const int NIGHTSTARTHOUR = 21;
const int NIGHTENDHOUR = 5;

void Init()
{
	srand((unsigned int)time(NULL));

	screensManager.GetView().setSize(screensManager.GetWindow().getDefaultView().getSize());
	screensManager.GetView().setCenter(screensManager.GetWindow().getDefaultView().getCenter());

	//Restart timer so that it's zero when the window actually starts
	screensManager.m_timer.restart();
	while (screensManager.GetWindow().isOpen())
	{
		screensManager.m_elapsedTime += screensManager.m_timer.restart().asSeconds();
		if (screensManager.m_elapsedTime >= screensManager.m_timePerFrame)
		{
			screensManager.m_elapsedTime -= screensManager.m_timePerFrame;

			sf::Event event;
			while (screensManager.GetWindow().pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					screensManager.GetWindow().close();
				if (event.type == sf::Event::TextEntered)
				{
					if (event.text.unicode < 128)
					{
						//Pass to userinputmanager to handle all necessary steps
						userInputManager.TextEnteredEvent(event);
					}
				}
			}

			//Frame Updates
			screensManager.m_mousePos = screensManager.GetWindow().mapPixelToCoords(sf::Mouse::getPosition(screensManager.GetWindow()));
			Utilities::Update();
			userInputManager.Update(sf::seconds(screensManager.m_timePerFrame));
			guiManager.Update();

			//FPS Counter
			guiManager.GetCustomTextsMap()["fpsText"].ChangeText("FPS: " + std::to_string((unsigned int)Utilities::getFPS(sf::seconds(screensManager.m_elapsedTime))));
		}

		//Begin render loop here
		{
			
			screensManager.m_bounds = screensManager.GetViewCullingBounds();

			screensManager.GetWindow().setView(screensManager.GetView());
			/*********** Clear the screen ******************/
			screensManager.GetWindow().clear();

			for (unsigned int cx = screensManager.m_bounds[0]; cx < screensManager.m_bounds[1]; cx++)
			{
				for (unsigned int cy = screensManager.m_bounds[2]; cy < screensManager.m_bounds[3]; cy++)
				{
					if (editor.m_roomMap[cx][cy].GetScreenTag() == screensManager.GetCurrentScreenTag())
						screensManager.GetWindow().draw(editor.m_roomMap[cx][cy].GetSprite());
				}
			}

			/*********** Draw the GUI to the screen ******************/
			guiManager.DrawToWindow();


			/*********** Display the screen ******************/
			screensManager.GetWindow().display();
		}
	}
}

int main()
{
	//Set up logger
	debug.Start();

	//Load database of ALL tiles
	editor.LoadListOfPossibleAnims(editor.m_tilesList);
	//Load editor resources
	editor.LoadEditorResources();

	//Run the editor!
	Init();

	return 0;
}

