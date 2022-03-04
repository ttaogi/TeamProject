#include "Stdafx.h"

#include "SteppingStone.h"

#include "Player.h"

#pragma region left
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
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	stripe->render(getMemDC(), renderPos.x, renderPos.y);
}

bool SteppingStoneLeft::interact(Player* player)
{
	if(player) player->setBounce(DIRECTION::LEFT);
	return true;
}

SteppingStoneLeft::SteppingStoneLeft()
{
	type = OBJECT_TYPE::STEPPING_STONE_LEFT;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

SteppingStoneLeft::~SteppingStoneLeft() { release(); }
#pragma endregion left

#pragma region top
HRESULT SteppingStoneTop::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::STEPPING_STONE_TOP;
	animator = NULL;
	scene = scenePtr;
	// SteppingStone*.
	stripe = IMAGEMANAGER->findImage(KEY_STEPPING_STONE_TOP);

	return S_OK;
}

void SteppingStoneTop::release(void) { }

void SteppingStoneTop::update(void) { }

void SteppingStoneTop::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	stripe->render(getMemDC(), renderPos.x, renderPos.y);
}

bool SteppingStoneTop::interact(Player * player)
{
	if (player) player->setBounce(DIRECTION::TOP);
	return true;
}

SteppingStoneTop::SteppingStoneTop()
{
	type = OBJECT_TYPE::STEPPING_STONE_TOP;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

SteppingStoneTop::~SteppingStoneTop() { release(); }
#pragma endregion top

#pragma region right
HRESULT SteppingStoneRight::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::STEPPING_STONE_RIGHT;
	animator = NULL;
	scene = scenePtr;
	// SteppingStone*.
	stripe = IMAGEMANAGER->findImage(KEY_STEPPING_STONE_RIGHT);

	return S_OK;
}

void SteppingStoneRight::release(void) { }

void SteppingStoneRight::update(void) { }

void SteppingStoneRight::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	stripe->render(getMemDC(), renderPos.x, renderPos.y);
}

bool SteppingStoneRight::interact(Player* player)
{
	if (player) player->setBounce(DIRECTION::RIGHT);
	return true;
}

SteppingStoneRight::SteppingStoneRight()
{
	type = OBJECT_TYPE::STEPPING_STONE_RIGHT;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

SteppingStoneRight::~SteppingStoneRight() { release(); }
#pragma endregion right

#pragma region bottom
HRESULT SteppingStoneBottom::init(Scene * scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::STEPPING_STONE_BOTTOM;
	animator = NULL;
	scene = scenePtr;
	// SteppingStone*.
	stripe = IMAGEMANAGER->findImage(KEY_STEPPING_STONE_BOTTOM);

	return S_OK;
}

void SteppingStoneBottom::release(void) { }

void SteppingStoneBottom::update(void) { }

void SteppingStoneBottom::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	stripe->render(getMemDC(), renderPos.x, renderPos.y);
}

bool SteppingStoneBottom::interact(Player * player)
{
	if (player) player->setBounce(DIRECTION::BOTTOM);
	return true;
}

SteppingStoneBottom::SteppingStoneBottom()
{
	type = OBJECT_TYPE::STEPPING_STONE_BOTTOM;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

SteppingStoneBottom::~SteppingStoneBottom() { release(); }
#pragma endregion bottom
