#include "stdafx.h"
#include "AnimationClass.h"
#include "AnimationFrame.h"

bool Animation::LoadAnimation(std::string _fileName)
{
	tinyxml2::XMLDocument	doc;
	std::string				docLoc;

	docLoc = "Resources/Animations/";
	docLoc += _fileName;

	doc.LoadFile(docLoc);

	tinyxml2::XMLElement* root = doc.FirstChildElement();

	return false;
}

bool Animation::PlayAnimation(std::string _animationName)
{
	return false;
}