#pragma once

#include "GameNode.h"

class Image;
class Object;
class Player;
class Slime;

class Scene : public GameNode
{
private:
protected:
	MapInfo* mapInfo;
	Player* player;
	Image* minimap;
	double bgmLength;
	double sceneInitTime;
	std::vector<Object*> objectVec;
	std::vector<Object*> effectVec;
public:
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	MapInfo* getMapInfo();
	void setMapInfo(MapInfo* _mapInfo) { mapInfo = _mapInfo; }
	Player* getPlayer();
	std::vector<Object*>* getObjectVec();
	std::vector<Object*>* getEffectVec();
	Object* getObject(POINT _pos);

	Scene() { };
	virtual ~Scene() { };
};