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

	debug.Log(0, "Loading ANIMATION '" + _fileName + "' ...");
	doc.LoadFile(docLoc.c_str());

	tinyxml2::XMLElement* root = doc.FirstChildElement("Animation");

	textureLoc = root->FirstChildElement("Meta")->FirstChildElement("Texture")->GetText();
	soundLoc = root->FirstChildElement("Meta")->FirstChildElement("Sound")->GetText();
	numFrames = std::stoi(root->FirstChildElement("Meta")->FirstChildElement("NumFrames")->GetText());


	//Try to load TEXTURE file
	if (textureLoc != "###")
		graphicsManager.LoadTexture(textureLoc);

	//Try to load SOUND file
	if(soundLoc != "###")
		audioManager.LoadSound(soundLoc);

	//If either field is empty, animation file is broken
	if (textureLoc == "" || soundLoc == "")
		return false;

	//Create handle for parsing through all of the frames
	tinyxml2::XMLElement* frame = root->FirstChildElement("Frame");
	for (unsigned int cnt = 0; cnt < numFrames; cnt++)
	{
		AnimationFrame	curFrame;
		unsigned int	_x, _y, _width, _height, _ms;

		//Read data from XML file
		_y = std::stoi(frame->FirstChildElement("b1")->GetText());
		_x= std::stoi(frame->FirstChildElement("b2")->GetText());
		_width = std::stoi(frame->FirstChildElement("b3")->GetText());
		_height = std::stoi(frame->FirstChildElement("b4")->GetText());

		_ms = std::stoi(frame->FirstChildElement("ms")->GetText());


		//Set values in curFrame to those that were read from file
		curFrame.SetTextureBounds(_x, _y, _width, _height);
		curFrame.SetFrameDuration(_ms);
		curFrame.SetTexture(textureLoc);


		//Save curFrame into the animationList
		animationList.push_back(curFrame);


		//Move on to the next frame
		frame = frame->NextSiblingElement("Frame");
	}

	//Save the loaded animation to the class
	m_animations.insert( std::pair<std::string, std::vector<AnimationFrame>>(_fileName, animationList) );
	debug.Log(0, "Successfully loaded ANIMATION '" + _fileName + "'!");
	return true;
}

bool Animation::BeginAnimation(std::string _animationName)
{
	m_sprite.setTexture(graphicsManager.GetTexturesMap()[m_animations[_animationName][0].GetTexture()]);
	m_sprite.setTextureRect(m_animations[_animationName][0].GetTextureBounds());
	m_timeSinceLastUpdate = sf::Time::Zero;


	m_CurrentAnim = _animationName;
	m_currentAnimFrame = 0;
	return true;
}

std::string Animation::GetCurrentAnim()
{
	return m_CurrentAnim;
}

sf::Sprite & Animation::GetSprite()
{
	return m_sprite;
}

void Animation::Update(sf::Time _deltaTime)
{
	m_timeSinceLastUpdate += _deltaTime;
	//Check if time since last update is longer than animation frame time
	if (m_timeSinceLastUpdate > m_animations[m_CurrentAnim][m_currentAnimFrame].GetFrameDuration())
	{
		//If so, reduce timer by elapsed time and increment frame
		m_timeSinceLastUpdate -= m_animations[m_CurrentAnim][m_currentAnimFrame].GetFrameDuration();
		m_currentAnimFrame++;

		//Check if animation has more frames
		if (m_currentAnimFrame >= m_animations[m_CurrentAnim].size())
		{
			//Loop back otherwise
			m_currentAnimFrame = 0;
		}
		
		//Set the sprite to the correct texture box
		m_sprite.setTextureRect(m_animations[m_CurrentAnim][m_currentAnimFrame].GetTextureBounds());
	}
}
