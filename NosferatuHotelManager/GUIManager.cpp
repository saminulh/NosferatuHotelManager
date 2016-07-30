#include "stdafx.h"
#include "GUIManager.h"
#include "TextStruct.h"
#include "Button.h"

GUIManager::GUIManager()
{
}

GUIManager::~GUIManager()
{
}

void GUIManager::Update()
{
	///TODO: Change the timePerFrames to elapsedTime once the drawing loop is seperated from the logic loop

	//Iterate through the animatios map and update everything
	for (auto& cnt : animationsMap)
	{
		cnt.second.Update(sf::seconds(screensManager.m_timePerFrame));
	}

	//Iterate through the buttons map and update everything
	for (auto& cnt : buttonsMap)
	{
		cnt.second.Update(sf::seconds(screensManager.m_timePerFrame));
	}

	///TODO: Add any other GUI elements that need updating here
	///IMPORTANT NOTE: Ensure each thing is using the correct (static vs. variable) timestep
}

void GUIManager::DrawToWindow()
{
	//Draw all of the GUI elements
	//Start with images
	for (auto& cnt : animationsMap)
	{
		screensManager.GetWindow().draw(cnt.second.GetSprite());
	}

	//Then buttons
	for (auto& cnt : buttonsMap)
	{
		screensManager.GetWindow().draw(cnt.second.GetSprite());
		screensManager.GetWindow().draw(cnt.second.GetButtonText().GetOutlineTopLeft());
		screensManager.GetWindow().draw(cnt.second.GetButtonText().GetOutlineTopRight());
		screensManager.GetWindow().draw(cnt.second.GetButtonText().GetOutlineBottomLeft());
		screensManager.GetWindow().draw(cnt.second.GetButtonText().GetOutlineBottomRight());
		screensManager.GetWindow().draw(cnt.second.GetButtonText().GetMainText());
	}

	//Then custom texts
	for (auto& cnt : customTextsMap)
	{
		screensManager.GetWindow().draw(cnt.second.GetOutlineTopLeft());
		screensManager.GetWindow().draw(cnt.second.GetOutlineTopRight());
		screensManager.GetWindow().draw(cnt.second.GetOutlineBottomLeft());
		screensManager.GetWindow().draw(cnt.second.GetOutlineBottomRight());
		screensManager.GetWindow().draw(cnt.second.GetMainText());
	}

	//Finally, texts
	//Please use custom texts for GUIs and save sf::Texts for debug uses only
	for (auto& cnt : textsMap)
	{
		screensManager.GetWindow().draw(cnt.second);
	}
}

std::map<std::string, CustomText>& GUIManager::GetCustomTextsMap()
{
	return customTextsMap;
}

std::map<std::string, sf::Text>& GUIManager::GetSFTextsMap()
{
	return textsMap;
}

std::map<std::string, Animation>& GUIManager::GetAnimationsMap()
{
	return animationsMap;
}

std::map<std::string, Button>& GUIManager::GetButtonsMap()
{
	return buttonsMap;
}
