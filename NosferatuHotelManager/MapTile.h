#pragma once
#include "stdafx.h"
#include "AnimationClass.h"

class MapTile : public Animation
{
public:
	//Universal tile id - assigned as the tile is loaded - regardless of floor
	unsigned int		m_tileID;
	//Sub-space to which this tile belongs - basically the file name plus tme it was loaded
	unsigned int		m_roomID;
	//Map/floor to which this tile belongs - generated on load
	unsigned int		m_floorNumber;
	//Code for the activity/activities that can be performed here
	unsigned int		m_tileActivityCode;

	//Tile ABSOLUTE position (relative to top left of the MAP)
	//Not to be confused with the position in the map files - 
	//	those are relative to the top left of the ROOM
	float				m_xPos;
	float				m_yPos;
	
	//Must this tile connect to another room exit tile
	bool				m_isRoomExit;
	//Used for sometimes wall/sometimes walkable tiles
	bool				m_isDoor;
	//Can this tile be walked upon
	bool				m_isSolid;
};