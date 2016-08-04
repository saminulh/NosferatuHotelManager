#include "stdafx.h"
#include "AnimationFrame.h"
#include "AnimationClass.h"
#include "AnimationFrame.h"
#include "GraphicsManager.h"

Animation::Animation()
{
}

Animation::Animation(const Animation & _obj)
{
	m_sprite					= _obj.m_sprite;
	m_animations				= _obj.m_animations;
	m_timeSinceLastUpdate		= _obj.m_timeSinceLastUpdate;
	m_CurrentAnim				= _obj.m_CurrentAnim;
	m_currentAnimFrame			= _obj.m_currentAnimFrame;
	m_screenTag					= _obj.m_screenTag;
}

Animation::~Animation()
{
}

///TODO: Make this function smart enough to not reload the same damn animation 10000s of times when loading maps, etc.
bool Animation::LoadAnimation(std::string _fileName)
{
	tinyxml2::XMLDocument		doc;
	std::string					docLoc;

	std::string					textureLoc;
	std::string					soundLoc;
	unsigned int				numFrames;

	std::vector<AnimationFrame>	animationList;



	//Set the search folder
	docLoc = "Resources/Animations/";
	docLoc += _fileName;

	//Log to debug - maybe this could be removed
	debug.Log(0, "Loading ANIMATION '" + _fileName + "' ...");
	//Load the actual file (string must be passed as a c-string)
	tinyxml2::XMLError err = doc.LoadFile(docLoc.c_str());
	
	if (err != tinyxml2::XML_SUCCESS)
	{
		debug.Log(3, "Error reading XML file!");
	}

	//Get access to root element
	tinyxml2::XMLElement* root = doc.FirstChildElement("Animation");

	//Grab necessary data as std::string
	textureLoc = root->FirstChildElement("Meta")->FirstChildElement("Texture")->GetText();
	soundLoc = root->FirstChildElement("Meta")->FirstChildElement("Sound")->GetText();
	numFrames = std::stoi(root->FirstChildElement("Meta")->FirstChildElement("NumFrames")->GetText());


	//Try to load TEXTURE file - the '###' is reserved, in case the animation does not require a texture/sound effect
	if (textureLoc != "###")
		graphicsManager.LoadTexture(textureLoc);

	//Try to load SOUND file
	if(soundLoc != "###")
		audioManager.LoadSound(soundLoc);

	//If either field is empty, animation file is broken
	if (textureLoc == "" || soundLoc == "")
	{
		debug.Log(3, "Error loading ANIMATION '" + _fileName + "' - either the required sound or texture were not included in the file! To create an animation" \
			+ " without a texture or sound, use '###' in place of a texture or sound file name!");
		return false;
	}

	//Create handle for parsing through all of the frames
	tinyxml2::XMLElement* frame = root->FirstChildElement("Frame");
	for (unsigned int cnt = 0; cnt < numFrames; cnt++)
	{
		AnimationFrame	curFrame;
		unsigned int	_x, _y, _width, _height, _ms;

		//Read data from XML file - for some reason x and y are reversed; this seems to work though, so whatever
		_y = std::stoi(frame->FirstChildElement("b1")->GetText());
		_x= std::stoi(frame->FirstChildElement("b2")->GetText());
		_width = std::stoi(frame->FirstChildElement("b3")->GetText());
		_height = std::stoi(frame->FirstChildElement("b4")->GetText());

		_ms = std::stoi(frame->FirstChildElement("ms")->GetText());

		//Set values in curFrame to those that were read from file
		curFrame.SetTextureBounds(_x, _y, _width, _height);
		curFrame.SetFrameDuration(_ms);
		curFrame.SetTexture(textureLoc);

		if (cnt == 0)
		{
			curFrame.SetSoundEffect(soundLoc);
		}

		//Save curFrame into the animationList
		animationList.push_back(curFrame);


		//Move on to the next frame
		frame = frame->NextSiblingElement("Frame");
	}

	//Save the sound effect
	m_soundEffects.insert(std::pair<std::string, sf::SoundBuffer>(_fileName, audioManager.GetSoundsList()[soundLoc]));

	//Save the loaded animation to the class
	m_animations.insert( std::pair<std::string, std::vector<AnimationFrame>>(_fileName, animationList) );
	debug.Log(0, "Successfully loaded ANIMATION '" + _fileName + "'!");
	return true;
}

bool Animation::BeginAnimation(std::string _animationName)
{
	//Set the sprite's texture and texture bounding box (subset of the texture to actually be displayed)
	m_sprite.setTexture(graphicsManager.GetTexturesMap()[m_animations[_animationName][0].GetTexture()]);
	m_sprite.setTextureRect(m_animations[_animationName][0].GetTextureBounds());
	//IMPORTANT: Initialize the time since last update to zero, otherwise it will have a gibberish default/uninitialized value
	m_timeSinceLastUpdate = sf::Time::Zero;

	//Set the current animation to this one ... obviously
	m_CurrentAnim = _animationName;
	
	//Check that a sound was meant to be loaded
	if (m_animations[_animationName][0].GetSoundEffect() != "###")
	{
		//Play the corresponding sound
		m_sound.setBuffer(m_soundEffects[_animationName]);
		m_sound.play();
	}

	
	//Start at the first frame (to make sure that jumping from a longer animation to a shorter one
	//doesn't result in vector out of range errors)
	///TODO: Perhaps choose a random animation frame rather than the first one (?)
	m_currentAnimFrame = 0;
	return true;
}

std::string& Animation::GetCurrentAnim()
{
	return m_CurrentAnim;
}

sf::Sprite & Animation::GetSprite()
{
	return m_sprite;
}

std::string & Animation::GetSoundEffect()
{
	return m_animations[m_CurrentAnim][0].GetSoundEffect();
}

sf::Sound & Animation::GetSound()
{
	return m_sound;
}

void Animation::Update(sf::Time& _deltaTime)
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

void Animation::ChangeScreenTag(ScreensManager::ScreenTag _newTag)
{
	m_screenTag = _newTag;
}

ScreensManager::ScreenTag Animation::GetScreenTag()
{
	return m_screenTag;
}

void Animation::AssignAnimation(std::string& _anim, Animation & _ref)
{
	m_animations.clear();
	m_animations.insert(std::pair < std::string, std::vector<AnimationFrame>>(_anim, _ref.m_animations[_anim]));
}
