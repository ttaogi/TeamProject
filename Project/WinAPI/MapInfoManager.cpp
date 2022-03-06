#include "Stdafx.h"

#include "MapInfoManager.h"

#include "bat.h"
#include "Attack.h"
#include "Body.h"
#include "Bomb.h"
#include "Head.h"
#include "Heal.h"
#include "Money.h"
#include "Necrodancer.h"
#include "Object.h"
#include "Scene.h"
#include "Shopkeeper.h"
#include "Skeleton.h"
#include "Slime.h"
#include "slimeBlue.h"
#include "Stair.h"
#include "SteppingStone.h"
#include "Torch.h"
#include "Wall.h"
#include "Player.h"

Tile::Tile() { }

Tile::~Tile() { release(); }

HRESULT Tile::init(TILE_TYPE _type, POINT _pos)
{
	switch (_type) {
	case TILE_TYPE::EMPTY:
		isBlocked = true;
		stripe = NULL;
		minimapStripe = NULL;
		break;
	case TILE_TYPE::DIRT:
		isBlocked = false;
		stripe = IMAGEMANAGER->findImage(KEY_TILE_DIRT);
		minimapStripe = IMAGEMANAGER->findImage(KEY_TILE_DIRT_MINIMAP);
		break;
	default:
		isBlocked = true;
		stripe = NULL;
		minimapStripe = NULL;
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
		POINT renderPos = GridPointToPixelPointLeftTop(pos);
		POINT revision = CAMERAMANAGER->getRevision();

		renderPos.x -= revision.x;
		renderPos.y -= revision.y;

		stripe->render(_hdc, renderPos.x, renderPos.y);
	}
}

void Tile::renderMinimap(HDC _hdc)
{
	if (minimapStripe)
	{
		POINT renderPos = GridPointToPixelPointLeftTopMiniMap(pos);
		minimapStripe->render(_hdc, renderPos.x, renderPos.y);
	}
}

///////////////////////////////
///////////////////////////////

MapInfo::MapInfo() { }

MapInfo::~MapInfo() { release(); }

HRESULT MapInfo::init(const std::string _fileName, Scene* _scene)
{
	
	release();
	scene = _scene;
	TiXmlDocument doc;

	cout << "####################" << endl;
	cout << "MapInfo Init." << endl;

	if (XmlManager::loadFile(doc, _fileName))
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

		XmlManager::getAttributeValueDouble(interval, "interval", &turnInterval);
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
					Wall* obj = new Wall();
					if(SUCCEEDED(obj->init((OBJECT_TYPE)objectType, POINT{ i, j },_scene) ))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::MONSTER_SLIME)
				{
					Slime* obj = new Slime();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if(objectType == (int)OBJECT_TYPE::MONSTER_SLIME_BLUE)
				{
					SlimeBlue* obj = new SlimeBlue();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::MONSTER_SKELETON)
				{
					Skeleton* obj = new Skeleton();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::MONSTER_BAT)
				{
					Bat* obj = new Bat();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::MONSTER_NECRODANCER)
				{
					Necrodancer* obj = new Necrodancer();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::STEPPING_STONE_LEFT)
				{
					SteppingStoneLeft* obj = new SteppingStoneLeft();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::STEPPING_STONE_TOP)
				{
					SteppingStoneTop* obj = new SteppingStoneTop();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::STEPPING_STONE_RIGHT)
				{
					SteppingStoneRight* obj = new SteppingStoneRight();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::STEPPING_STONE_BOTTOM)
				{
					SteppingStoneBottom* obj = new SteppingStoneBottom();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::ITEM_MONEY)
				{
					Money* obj = new Money();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
					{
						int quantity;
						XmlManager::getAttributeValueInt(data, "quantity", &quantity);
						obj->setQuantity(quantity);
						objectVec.push_back(obj);
					}
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::ITEM_HEAL_APPLE)
				{
					Heal* obj = new Heal();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::ITEM_BOMB)
				{
					Bomb* obj = new Bomb();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_HEAD)
				{
					Head* obj = new Head();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_BOBY)
				{
					Body* obj = new Body();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_ATTACK_DAGGER)
				{
					Dagger* obj = new Dagger();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_ATTACK_BROADSWORD)
				{
					BroadSword* obj = new BroadSword();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_TORCH)
				{
					Torch* obj = new Torch();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::EUIP_ATTACK_GOLDENLUTE)
				{
					Goldenlute* obj = new Goldenlute();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::STAIR)
				{
					Stair* obj = new Stair();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
				else if (objectType == (int)OBJECT_TYPE::NPC_SHOP)
				{
					Shopkeeper* obj = new Shopkeeper();
					if (SUCCEEDED(obj->init(_scene, POINT{ i, j })))
						objectVec.push_back(obj);
					else
					{
						SAFE_RELEASE(obj);
						SAFE_DELETE(obj);
					}
				}
			}

			tileMap.push_back(vec);
		}

		/*cout << "********************" << endl;
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
		cout << "********************" << endl;*/
	}
	else return E_FAIL;

	cout << "####################" << endl;

	return S_OK;
}

void MapInfo::release()
{
	cout << "MapInfo release." << endl;
	scene = NULL;
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
		for (int x = 0; x < size.x; ++x)
		{
			int deltaX = abs(x - scene->getPlayer()->getPos().x);
			int deltaY = abs(y - scene->getPlayer()->getPos().y);
			if ((deltaX + deltaY) < PLAYERINFOMANAGER->getViewDistance())
				tileMap[x][y]->render(_hdc);
		}
}

void MapInfo::renderMinimap(HDC _hdc)
{
	for (int y = 0; y < size.y; ++y)
		for (int x = 0; x < size.x; ++x)
			tileMap[x][y]->renderMinimap(_hdc);
}

///////////////////////////////
///////////////////////////////

HRESULT MapInfoManager::init()
{
	cout << "####################" << endl;
	cout << "MapInfoManager init." << endl;

	MapInfo* exampleMap = new MapInfo();
	MapInfo* dungeonMap = new MapInfo();
	MapInfo* bossMap = new MapInfo();

	mapInfoMap.insert(make_pair(MAP_ID::EXAMPLE_MAP, exampleMap));
	mapInfoMap.insert(make_pair(MAP_ID::DUGEON_MAP, dungeonMap));
	mapInfoMap.insert(make_pair(MAP_ID::BOSS_MAP, bossMap));

	cout << "####################" << endl;

	return S_OK;
}

void MapInfoManager::release()
{
	cout << "####################" << endl;
	cout << "MapInfoManager release." << endl;
	for (auto iter = mapInfoMap.begin(); iter != mapInfoMap.end(); ++iter)
	{
		iter->second->release();
		SAFE_DELETE(iter->second);
	}
	mapInfoMap.clear();
	cout << "####################" << endl;
}

MapInfo* MapInfoManager::getMapInfo(MAP_ID _mapId, Scene* _scene)
{
	auto iter = mapInfoMap.find(_mapId);
	if (iter == mapInfoMap.end()) return NULL;
	else
	{
		_scene->setMapInfo(iter->second);
		if(SUCCEEDED( iter->second->init(MapIdToKeyString(_mapId), _scene) ))
			return iter->second;
		else return NULL;
	}
}
