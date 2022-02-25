#pragma once

#include "SingletonBase.h"

#include "Enums.h"

class Object;

class Tile {
public:
	bool isBlocked;
	TILE_TYPE type;
	POINT pos;
	Image* stripe;

	Tile();
	~Tile();

	HRESULT init(TILE_TYPE _type, POINT _pos);
	void release();
	void render(HDC _hdc);
};

class MapInfo {
private:
	POINT startPos;
	POINT size;
	float turnInterval;
	std::vector<std::vector<Tile*>> tileMap;
	std::vector<Object*> objectVec;
public:
	MapInfo();
	~MapInfo();

	HRESULT init(const std::string _fileName);
	void release();
	void render(HDC _hdc);

	POINT getStartPos() const { return startPos; }
	POINT getSize() const { return size; }
	float getTurnInterval() const { return turnInterval; }
	std::vector<std::vector<Tile*>>* getTileMap() { return &tileMap; }
	std::vector<Object*> getObjectVec() const { return objectVec; }
};

class MapInfoManager : public SingletonBase<MapInfoManager> {
private:
	std::map<MAP_ID, MapInfo*> mapInfoMap;
public:
	MapInfoManager() { }
	~MapInfoManager() { }

	HRESULT init();
	void release();

	MapInfo* getMapInfo(MAP_ID _mapId);
};