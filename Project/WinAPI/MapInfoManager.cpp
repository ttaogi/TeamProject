#include "Stdafx.h"

#include "MapInfoManager.h"

#include "Object.h"
#include "Scene.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Wall.h"

Tile::Tile() { }

Tile::~Tile() { release(); }

HRESULT Tile::init(TILE_TYPE _type, POINT _pos)
{
	switch (_type) {
	case TILE_TYPE::EMPTY:
		isBlocked = true;
		stripe = NULL;
		break;
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

HRESULT MapInfo::init(const std::string _fileName, Scene* _scene)
{
	release();

	TiXmlDocument doc;

	cout << "####################" << endl;
	cout << "MapInfo Init." << endl;

	if (XmlManager::loadFile(doc, XML_DOC_EXAMPLE_MAP))
	{
		TiXmlElement* root = XmlManager::firstChildElement(doc, "ROOT");
		TiXmlElement* interval = XmlManager::firstChildElement(root, "turnInterval");
		TiXmlElement* startPosInfo = XmlManager::firstChildElement(root, "startPos");
		TiXmlElement* bgm = XmlManager::firstChildElement(root, "bgm");
		TiXmlElement* map = XmlManager::firstChildElement(root, "map");
		int bgmId = 0;
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

		XmlManager::getAttributeValueInt(bgm, "sound_id", &bgmId);
		XmlManager::getAttributeValueFloat(bgm, "play_time", &bgmPlayTime);
		bgmKey = SoundIdToKeyString((SOUND_ID)bgmId);

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
				int objectType = 0;
				Tile* tile = new Tile();

				XmlManager::getAttributeValueInt(data, "type", &tileType);
				tile->init((TILE_TYPE)tileType, POINT{ i, j });
				vec.push_back(tile);

				XmlManager::getAttributeValueInt(data, "object", &objectType);
				if (objectType == (int)OBJECT_TYPE::WALL_UNBREAKABLE ||
					objectType == (int)OBJECT_TYPE::WALL_DIRT ||
					objectType == (int)OBJECT_TYPE::WALL_SHOP)
				{
					Wall* wall = new Wall();
					if(SUCCEEDED( wall->init((OBJECT_TYPE)objectType, POINT{ i, j }) ))
						objectVec.push_back(wall);
					else
					{
						SAFE_RELEASE(wall);
						SAFE_DELETE(wall);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::MONSTER_SLIME)
				{
					Slime* slime = new Slime();
					if (SUCCEEDED(slime->init(_scene, POINT{ i, j })))
						objectVec.push_back(slime);
					else
					{
						SAFE_RELEASE(slime);
						SAFE_DELETE(slime);
					}
				}
				else if(objectType == (int)OBJECT_TYPE::MONSTER_SLIME_BLUE)
				{
					SlimeBlue* slimeBlue = new SlimeBlue();
					if (SUCCEEDED(slimeBlue->init(_scene, POINT{ i, j })))
						objectVec.push_back(slimeBlue);
					else
					{
						SAFE_RELEASE(slimeBlue);
						SAFE_DELETE(slimeBlue);
					}
				}
			}

			tileMap.push_back(vec);
		}

		cout << "********************" << endl;
		cout << "MapInfo file : " << _fileName << endl;
		cout << "tile map" << endl;
		for (int y = 0; y < mapSizeY; ++y)
		{
			for (int x = 0; x < mapSizeX; ++x)
				cout << (int)(tileMap[x][y]->type) << "\t";
			cout << endl;
		}
		cout << "tile map" << endl;
		cout << "object vector" << endl;
		for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
		{
			cout << (int)(*iter)->getType() << " ["
				<< (*iter)->getPos().x << " : "
				<< (*iter)->getPos().y << "]" << endl;
		}
		cout << "object vector" << endl;
		cout << "********************" << endl;
	}
	else return E_FAIL;

	cout << "####################" << endl;

	return S_OK;
}

void MapInfo::release()
{
	cout << "MapInfo release." << endl;
	bgmKey = "";
	bgmPlayTime = 0.0f;
	startPos = POINT{ 0, 0 };
	size = POINT{ 0, 0 };
	turnInterval = 0.0f;

	for (auto iter = tileMap.begin(); iter != tileMap.end(); ++iter)
	{
		for (auto iter2 = iter->begin(); iter2 != iter->end(); ++iter2)
		{
			SAFE_RELEASE((*iter2));
			SAFE_DELETE((*iter2));
		}
	}
	tileMap.clear();

	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		SAFE_RELEASE((*iter));
		SAFE_DELETE((*iter));
	}
	objectVec.clear();
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
	cout << "MapInfoManager init." << endl;
	IMAGEMANAGER->addImage(KEY_TILE_DIRT, DIR_TILE_DIRT, TILE_SIZE, TILE_SIZE, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_TILE_DIRT)->initForAlphaBlend();
	cout << "TILE DIRT : " << IMAGEMANAGER->findImage(KEY_TILE_DIRT) << endl;
	IMAGEMANAGER->addFrameImage(KEY_WALL_UNBREAKABLE, DIR_WALL_UNBREAKABLE, TILE_SIZE, TILE_SIZE * 2, 1, 1, 1, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_UNBREAKABLE)->initForAlphaBlend();
	cout << "WALL UNBREAKABLE : " << IMAGEMANAGER->findImage(KEY_WALL_UNBREAKABLE) << endl;
	IMAGEMANAGER->addFrameImage(KEY_WALL_DIRT, DIR_WALL_DIRT, TILE_SIZE * 16, TILE_SIZE * 2, 16, 1, 16, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_DIRT)->initForAlphaBlend();
	cout << "WALL DIRT : " << IMAGEMANAGER->findImage(KEY_WALL_DIRT) << endl;
	IMAGEMANAGER->addFrameImage(KEY_WALL_SHOP, DIR_WALL_SHOP, TILE_SIZE, TILE_SIZE * 2, 1, 1, 1, true, MAGENTA);
	IMAGEMANAGER->findImage(KEY_WALL_SHOP)->initForAlphaBlend();
	cout << "WALL SHOP : " << IMAGEMANAGER->findImage(KEY_WALL_SHOP) << endl;

	MapInfo* exampleMap = new MapInfo();

	mapInfoMap.insert(make_pair(MAP_ID::EXAMPLE_MAP, exampleMap));

	return S_OK;
}

void MapInfoManager::release()
{
	cout << "MapInfoManager release." << endl;
	for (auto iter = mapInfoMap.begin(); iter != mapInfoMap.end(); ++iter)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
	}
	mapInfoMap.clear();
}

MapInfo* MapInfoManager::getMapInfo(MAP_ID _mapId, Scene* _scene)
{
	auto iter = mapInfoMap.find(_mapId);
	if (iter == mapInfoMap.end()) return NULL;
	else
	{
		if(SUCCEEDED( iter->second->init(MapIdToKeyString(_mapId), _scene) ))
			return iter->second;
		else return NULL;
	}
}
