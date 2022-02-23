#include "Stdafx.h"

#include "MapInfoManager.h"

Tile::Tile() { }

Tile::~Tile() { release(); }

HRESULT Tile::init(TILE_TYPE _type, POINT _pos)
{
	switch (_type) {
	case TILE_TYPE::DIRT:
		isBlocked = false;
		stripe = IMAGEMANAGER->findImage(KEY_TILE_DIRT);
		break;
	default:
		isBlocked = true;
		stripe = NULL;
		break;
	}
	type = _type;
	pos = _pos;

	return S_OK;
}

void Tile::release() { }

void Tile::render(HDC _hdc)
{
	if (stripe)
	{
		stripe->render(_hdc, pos.x * TILE_SIZE, pos.y * TILE_SIZE);
	}
}

///////////////////////////////
///////////////////////////////

MapInfo::MapInfo() { }

MapInfo::~MapInfo() { release(); }

HRESULT MapInfo::init(const std::string _fileName)
{
	release();

	TiXmlDocument doc;

	cout << "####################" << endl;
	cout << "MapInfo Init." << endl;

	if (XmlManager::loadFile(doc, XML_DOC_EXAMPLE_MAP))
	{
		TiXmlElement* root = XmlManager::firstChildElement(doc, "ROOT");
		cout << "ROOT." << endl;
		TiXmlElement* interval = XmlManager::firstChildElement(root, "turnInterval");
		cout << "turnInterval." << endl;
		TiXmlElement* startPosInfo = XmlManager::firstChildElement(root, "startPos");
		cout << "startPos." << endl;
		TiXmlElement* map = XmlManager::firstChildElement(root, "map");
		cout << "map." << endl;
		int mapSizeX = 0;
		int mapSizeY = 0;
		int startX = 0;
		int startY = 0;

		XmlManager::getAttributeValueFloat(interval, "interval", &turnInterval);
		cout << "turn interval : " << turnInterval << endl;

		XmlManager::getAttributeValueInt(startPosInfo, "pos_x", &startX);
		XmlManager::getAttributeValueInt(startPosInfo, "pos_y", &startY);
		startPos = POINT{ startX, startY };
		cout << "start pos : " << startX << " : " << startY << endl;

		XmlManager::getAttributeValueInt(map, "num_x", &mapSizeX);
		XmlManager::getAttributeValueInt(map, "num_y", &mapSizeY);
		size = POINT{ mapSizeX, mapSizeY };
		cout << "size : " << mapSizeX << " : " << mapSizeY << endl;

		for (int i = 0; i < mapSizeX; ++i)
		{
			TiXmlElement* column = XmlManager::firstChildElement(map, "x_" + to_string(i));

			if (column == NULL) return E_FAIL;

			vector<Tile*> vec;
			vec.reserve(mapSizeY);

			for (int j = 0; j < mapSizeY; ++j)
			{
				TiXmlElement* data = XmlManager::firstChildElement(column, "y_" + to_string(j));

				if (data == NULL) return E_FAIL;

				int tileType = 0;
				Tile* tile = new Tile();
				XmlManager::getAttributeValueInt(data, "type", &tileType);
				tile->init((TILE_TYPE)tileType, POINT{ i, j });
				vec.push_back(tile);
			}

			tileMap.push_back(vec);
		}

		cout << "********************" << endl;
		cout << "MapInfo Init : " << _fileName << endl;
		cout << "map size : " << size.x << " : " << size.y << endl;
		cout << "start pos : " << startPos.x << " : " << startPos.y << endl;
		cout << "tile map" << endl;
		for (int y = 0; y < mapSizeY; ++y)
		{
			for (int x = 0; x < mapSizeX; ++x)
			{
				cout << x << ":" << y << "-"
					<< (int)(tileMap[x][y]->type) << "\t";
			}
			cout << endl;
		}
		cout << "tile map" << endl;
		cout << "####################" << endl;
	}
	else return E_FAIL;

	return S_OK;
}

void MapInfo::release()
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

void MapInfo::render(HDC _hdc)
{
	for (int y = 0; y < size.y; ++y)
	{
		for (int x = 0; x < size.x; ++x)
		{
			tileMap[x][y]->render(_hdc);
		}
	}
}

///////////////////////////////
///////////////////////////////

HRESULT MapInfoManager::init()
{
	IMAGEMANAGER->addImage(KEY_TILE_DIRT, DIR_TILE_DIRT, TILE_SIZE, TILE_SIZE, false, MAGENTA);
	IMAGEMANAGER->findImage(KEY_TILE_DIRT)->initForAlphaBlend();
	cout << "TILE DIRT : " << IMAGEMANAGER->findImage(KEY_TILE_DIRT) << endl;
	MapInfo* exampleMap = new MapInfo();

	if (FAILED(exampleMap->init(XML_DOC_EXAMPLE_MAP))) return E_FAIL;

	mapInfoMap.insert(make_pair(MAP_ID::EXAMPLE_MAP, exampleMap));

	return S_OK;
}

void MapInfoManager::release()
{
	for (auto iter = mapInfoMap.begin(); iter != mapInfoMap.end(); ++iter)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
	}
	mapInfoMap.clear();
}

MapInfo* MapInfoManager::getMapInfo(MAP_ID _mapId)
{
	auto iter = mapInfoMap.find(_mapId);
	if (iter == mapInfoMap.end()) return NULL;
	else return iter->second;
}
