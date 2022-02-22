#include "Stdafx/stdafx.h"

#include "Manager/MapInfoManager/MapInfoManager.h"

Tile::Tile() { }

Tile::~Tile() { Release(); }

HRESULT Tile::Init(TILE_TYPE _type, POINT _pos)
{
	switch (_type) {
	case TILE_TYPE::DIRT:
		isBlocked = false;
		stripe = IMG->FindImage(KEY_TILE_DIRT);
		break;
	default:
		isBlocked = true;
		stripe = NULL;
		break;
	}
	pos = _pos;

	return S_OK;
}

void Tile::Release() { }

///////////////////////////////
///////////////////////////////

MapInfo::MapInfo() { }

MapInfo::~MapInfo() { Release(); }

HRESULT MapInfo::Init(const std::wstring _fileName)
{
	Release();

	TiXmlDocument doc;
	wcout << L"MapInfo Init." << endl;

	if (XmlManager::LoadFile(doc, XML_DOC_EXAMPLE_MAP))
	{
		TiXmlElement* root = XmlManager::FirstChildElement(doc, L"ROOT");
		wcout << L"ROOT." << endl;
		TiXmlElement* interval = XmlManager::FirstChildElement(root, L"turnInterval");
		wcout << "turnInterval." << endl;
		TiXmlElement* startPosInfo = XmlManager::FirstChildElement(root, L"startPos");
		wcout << L"startPos." << endl;
		TiXmlElement* map = XmlManager::FirstChildElement(root, L"map");
		wcout << L"map." << endl;
		int mapSizeX = 0;
		int mapSizeY = 0;
		int startX = 0;
		int startY = 0;

		XmlManager::GetAttributeValueFloat(interval, L"interval", &turnInterval);
		wcout << L"turn interval : " << turnInterval << endl;

		XmlManager::GetAttributeValueInt(startPosInfo, L"pos_x", &startX);
		XmlManager::GetAttributeValueInt(startPosInfo, L"pos_y", &startY);
		startPos = POINT{ startX, startY };
		wcout << L"start pos : " << startX << L" : " << startY << endl;

		XmlManager::GetAttributeValueInt(map, L"num_x", &mapSizeX);
		XmlManager::GetAttributeValueInt(map, L"num_y", &mapSizeY);
		size = POINT{ mapSizeX, mapSizeY };
		wcout << L"size : " << mapSizeX << L" : " << mapSizeY << endl;

		for (int i = 0; i < mapSizeX; ++i)
		{
			TiXmlElement* column = XmlManager::FirstChildElement(map, L"x_" + to_wstring(i));

			if (column == NULL) return E_FAIL;

			vector<Tile*> vec;
			vec.reserve(mapSizeY);

			for (int j = 0; j < mapSizeY; ++j)
			{
				TiXmlElement* data = XmlManager::FirstChildElement(column, L"y_" + to_wstring(j));

				if (data == NULL) return E_FAIL;

				int tileType = 0;
				Tile* tile = new Tile();
				XmlManager::GetAttributeValueInt(data, L"type", &tileType);
				tile->Init((TILE_TYPE)tileType, POINT{ i, j });
				vec.push_back(tile);
			}

			tileMap.push_back(vec);
		}

		std::wcout << L"####################" << endl;
		std::wcout << L"MapInfo Init : " << _fileName << endl;
		std::wcout << L"map size : " << size.x << L" : " << size.y << endl;
		std::wcout << L"start pos : " << startPos.x << L" : " << startPos.y << endl;
		std::wcout << L"tile map" << endl;
		for (int y = 0; y < mapSizeY; ++y)
		{
			for (int x = 0; x < mapSizeX; ++x)
			{
				std::wcout << x << L":" << y << L"-"
					<< (int)tileMap[x][y]->type << L"\t";
			}
			std::wcout << endl;
		}
		std::wcout << L"tile map" << endl;
		std::wcout << L"####################" << endl;
	}
	else return E_FAIL;

	return S_OK;
}

void MapInfo::Release()
{
	for (auto iter = tileMap.begin(); iter != tileMap.end(); ++iter)
	{
		for (auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
		{
			SAFE_RELEASE((*iter2));
			SAFE_DELETE((*iter2));
		}
	}
	tileMap.clear();
	startPos = POINT{ 0, 0 };
	size = POINT{ 0, 0 };
}

///////////////////////////////
///////////////////////////////

HRESULT MapInfoManager::Init()
{
	MapInfo* exampleMap = new MapInfo();

	if (FAILED(exampleMap->Init(XML_DOC_EXAMPLE_MAP))) return E_FAIL;

	mapInfoMap.insert(make_pair(MAP_ID::EXAMPLE_MAP, exampleMap));

	return S_OK;
}

void MapInfoManager::Release()
{
	for (auto iter = mapInfoMap.begin(); iter != mapInfoMap.end(); ++iter)
	{
		iter->second->Release();
		SAFE_DELETE(iter->second);
	}
	mapInfoMap.clear();
}

MapInfo* MapInfoManager::GetMapInfo(MAP_ID _mapId)
{
	auto iter = mapInfoMap.find(_mapId);
	if (iter == mapInfoMap.end()) return NULL;
	else return iter->second;
}
