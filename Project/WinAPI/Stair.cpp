#include "Stdafx.h"

#include "Stair.h"

#include "MainGame.h"
#include "Scene.h"
#include "Player.h"
HRESULT Stair::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::STAIR;
	minimapStripe = IMAGEMANAGER->findImage(KEY_STAIR_MINIMAP);
	animator = NULL;
	scene = scenePtr;
	// Stair.
	stripe = IMAGEMANAGER->findImage(KEY_STAIR);
	nextSceneKey = KEY_SCENE_NONE;

	return S_OK;
}

void Stair::release(void) { }

void Stair::update(void) { }

void Stair::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < PLAYERINFOMANAGER->getViewDistance())
		stripe->render(getMemDC(), renderPos.x, renderPos.y);
}

void Stair::renderMinimap(HDC _hdc)
{
	if (minimapStripe)
	{
		POINT renderPos = GridPointToPixelPointLeftTopMiniMap(pos);
		minimapStripe->render(_hdc, renderPos.x, renderPos.y);
	}
}

bool Stair::interact(Player* player)
{
	if (nextSceneKey != KEY_SCENE_NONE) _mg->setNextScene(nextSceneKey);
	return true;
}

void Stair::setNextSceneKey(std::string _nextSceneKey) { nextSceneKey = _nextSceneKey; }

Stair::Stair()
{
	type = OBJECT_TYPE::STAIR;
	pos = POINT{ 0, 0 };
	animator = NULL;
	stripe = IMAGEMANAGER->findImage(KEY_STAIR);
	nextSceneKey = KEY_SCENE_NONE;
}

Stair::~Stair() { release(); }
