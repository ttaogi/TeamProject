#pragma once

#include "SingletonBase.h"

#include "Enums.h"

class Object;
class Scene;

class Tile {
public:
	bool isBlocked;
	TILE_TYPE type;
	POINT pos;
	Image* stripe;
	Image* minimapStripe;

	Tile();
	~Tile();

	HRESULT init(TILE_TYPE _type, POINT _pos);
	void release();
	void render(HDC _hdc);
	void renderMinimap(HDC _hdc);
};

class MapInfo {
private:
	std::string bgmKey;
	float bgmPlayTime;
	POINT startPos;
	POINT size;
	Scene* scene;
	double turnInterval;
	std::vector<std::vector<Tile*>> tileMap;
	std::vector<Object*> objectVec;
public:
	MapInfo();
	~MapInfo();

	HRESULT init(const std::string _fileName, Scene* _scene);
	void release();
	void render(HDC _hdc);
	void renderMinimap(HDC _hdc);

	std::string getBgmKey() const { return bgmKey; }
	float getBgmPlayTime() const { return bgmPlayTime; }
	POINT getStartPos() const { return startPos; }
	POINT getSize() const { return size; }
	double getTurnInterval() const { return turnInterval; }
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

	MapInfo* getMapInfo(MAP_ID _mapId, Scene* _scene);
};