#pragma once
#include "MapTile.h"

class Editor
{
public:
	std::vector<Animation>					m_tilesList;
	std::vector<std::vector<MapTile>>		m_roomMap;
	MapTile									m_currentTileProperties;

	static tinyxml2::XMLDocument			m_xml;

	Editor();

	void									Init();
	void									LoadMap(std::string _fileName);
	void									LoadEditorResources();
	void									LoadResources();
	void									CreateMap(std::string _fileName);
	void									SaveMap(std::string _FileName);

	MapTile&								GetCurrentTileProperties();
};