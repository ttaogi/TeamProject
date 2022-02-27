#include "Stdafx.h"

#include "SteppingStone.h"

HRESULT SteppingStoneLeft::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::STEPPING_STONE_LEFT;
	animator = NULL;
	scene = scenePtr;
	// SteppingStone*.
	stripe = IMAGEMANAGER->findImage(KEY_STEPPING_STONE_LEFT);

	return S_OK;
}

void SteppingStoneLeft::release(void) { }

void SteppingStoneLeft::update(void) { }

void SteppingStoneLeft::render(void)
{
	POINT p = GridPointToPixelPointCenter(pos);
	stripe->render(getMemDC(), p.x - stripe->getWidth() / 2,
		p.y - stripe->getHeight() / 2);
}

bool SteppingStoneLeft::interact(Player* player)
{
	//
	return true;
}

SteppingStoneLeft::SteppingStoneLeft()
{
	type = OBJECT_TYPE::STEPPING_STONE_LEFT;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

SteppingStoneLeft::~SteppingStoneLeft() { release(); }
