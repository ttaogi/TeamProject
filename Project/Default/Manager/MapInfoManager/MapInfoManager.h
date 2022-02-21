#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class Tile {
public:
	bool isBlocked;
	TILE_TYPE type;
	POINT pos;
	Image* stripe;

	Tile();
	~Tile();

	HRESULT Init(TILE_TYPE _type, POINT _pos);
	void Release();
};

class MapInfo {
private:
	POINT startPos;
	POINT size;
	std::vector<std::vector<Tile*>> tileMap;
public:
	MapInfo();
	~MapInfo();

	HRESULT Init(const std::wstring _fileName);
	void Release();

	std::vector<std::vector<Tile*>>* GetTileMap() { return &tileMap; }
	POINT GetStartPos() const { return startPos; }
	POINT GetSize() const { return size; }
};

class MapInfoManager : public SingletonBase<MapInfoManager> {
private:
	std::map<MAP_ID, MapInfo*> mapInfoMap;
public:
	MapInfoManager() { }
	~MapInfoManager() { }

	HRESULT Init();
	void Release();

	MapInfo* GetMapInfo(MAP_ID _mapId);
};