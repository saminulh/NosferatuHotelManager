#include "stdafx.h"
#include "AnimationFrame.h"
#include "AnimationClass.h"
#include "AnimationFrame.h"
#include "GraphicsManager.h"

bool Animation::LoadAnimation(std::string _fileName)
{
	tinyxml2::XMLDocument		doc;
	std::string					docLoc;

	std::string					textureLoc;
	std::string					soundLoc;
	unsigned int				numFrames;

	std::vector<AnimationFrame>	animationList;

	docLoc = "Resources/Animations/";
	docLoc += _fileName;

	debug.Log(1, "Loading ANIMATION '" + _fileName + "' ...");
	doc.LoadFile(docLoc.c_str());

	tinyxml2::XMLElement* root = doc.FirstChildElement("Animation");

	textureLoc = root->FirstChildElement("Meta")->FirstChildElement("Texture")->GetText();
	soundLoc = root->FirstChildElement("Meta")->FirstChildElement("Sound")->GetText();
	numFrames = std::stoi(root->FirstChildElement("Meta")->FirstChildElement("NumFrames")->GetText());


	//Try to load TEXTURE file
	graphicsManager.LoadTexture(textureLoc);

	///TODO: Try to load SOUND file


	//Create handle for parsing through all of the frames
	tinyxml2::XMLElement* frame = root->FirstChildElement("Frame");
	for (unsigned int cnt = 0; cnt < numFrames; cnt++)
	{
		AnimationFrame	curFrame;
		unsigned int	_x, _y, _width, _height, _ms;

		//Read data from XML file
		_x = std::stoi(frame->FirstChildElement("b1")->GetText());
		_y = std::stoi(frame->FirstChildElement("b2")->GetText());
		_width = std::stoi(frame->FirstChildElement("b3")->GetText());
		_height = std::stoi(frame->FirstChildElement("b4")->GetText());

		_ms = std::stoi(frame->FirstChildElement("ms")->GetText());


		//Set values in curFrame to those that were read from file
		curFrame.SetTextureBounds(_x, _y, _width, _height);
		curFrame.SetFrameDuration(_ms);
		curFrame.m_texture = &graphicsManager.GetTexturesMap()[textureLoc];


		//Save curFrame into the animationList
		animationList.push_back(curFrame);


		//Move on to the next frame
		frame = frame->NextSiblingElement("Frame");
	}

	//Save the loaded animation to the class
	m_animations.insert( std::pair<std::string, std::vector<AnimationFrame>>(_fileName, animationList) );
	debug.Log(1, "Successfully loaded ANIMATION '" + _fileName + "'!");
	return true;
}

bool Animation::BeginAnimation(std::string _animationName, sf::Sprite& _target)
{
	return false;
}