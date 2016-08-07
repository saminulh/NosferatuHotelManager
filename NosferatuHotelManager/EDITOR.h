#pragma once
#include "MapTile.h"

struct UsedAnimStruct
{
	std::string								refAnim;
	std::vector<Animation*>					referencesList;
};

class Editor
{
public:
	std::vector<Animation>					m_allTilesList;
	std::vector<Animation>					m_shortTilesList;
	std::vector<std::vector<MapTile>>		m_roomMap;
	MapTile									m_currentTileProperties;
	unsigned int							m_currentTileInShortList;
	std::string								m_tilesList;
	std::string								m_currentFile;

	std::vector<UsedAnimStruct>				m_animationsUsed;

	Animation								m_tempLoader;

	//static tinyxml2::XMLDocument			m_xml;

	Editor();

	void									Init();
	void									LoadMap(std::string& _fileName);
	void									LoadEditorResources();
	void									LoadResources();
	void									CreateMap(std::string& _fileName);
	void									SaveMap(std::string& _fileName);
	void									LoadListOfPossibleAnims(std::string& _fileName);

	void									AddUsedAnimation(std::string _anim, Animation* _user);
	void									RemoveUnusedAnimation(std::string _anim, Animation* _user);

	MapTile&								GetCurrentTileProperties();
};