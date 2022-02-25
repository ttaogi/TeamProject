#pragma once

#include "GameNode.h"

class Object;
class Player;
class Slime;

class Scene : public GameNode
{
private:
protected:
	MapInfo* mapInfo;
	Player* player;
	std::vector<Object*> objectVec;
public:
	virtual HRESULT init(void) = 0;
	virtual void release(void) = 0;
	virtual void update(void) = 0;
	virtual void render(void) = 0;

	MapInfo* getMapInfo();
	Player* getPlayer();
	std::vector<Object*>* getObjectVec();
	Object* getObject(POINT _pos);

	Scene() { };
	virtual ~Scene() { };
};