#include "Stdafx.h"

#include "Scene.h"

#include <queue>

#include "MainGame.h"
#include "Object.h"

MapInfo* Scene::getMapInfo() { return mapInfo; }

Player* Scene::getPlayer() { return player; }

std::vector<Object*>* Scene::getObjectVec() { return &objectVec; }

Object* Scene::getObject(POINT _pos)
{
	for (auto iter = objectVec.begin(); iter != objectVec.end(); ++iter)
	{
		POINT objPos = (*iter)->getPos();
		if (_pos.x == objPos.x && _pos.y == objPos.y)
			return *iter;
	}
	return NULL;
}
