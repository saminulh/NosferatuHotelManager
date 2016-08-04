#pragma once
#include "MapTile.h"

class Editor
{
public:
	std::vector<Animation>					m_allTilesList;
	std::vector<Animation>					m_shortTilesList;
	std::vector<std::vector<MapTile>>		m_roomMap;
	MapTile									m_currentTileProperties;
	unsigned int							m_currentTileInShortList;
	std::string								m_tilesList;

	static tinyxml2::XMLDocument			m_xml;

	Editor();

	void									Init();
	void									LoadMap(std::string& _fileName);
	void									LoadEditorResources();
	void									LoadResources();
	void									CreateMap(std::string& _fileName);
	void									SaveMap(std::string& _FileName);
	void									LoadListOfPossibleAnims(std::string& _fileName);

	MapTile&								GetCurrentTileProperties();
};