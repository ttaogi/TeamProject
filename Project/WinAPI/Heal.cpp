#include "stdafx.h"

#include "Heal.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Heal::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::ITEM_HEAL_APPLE;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::HEAL_APPLE);

	return S_OK;
}

void Heal::release(void) { }

void Heal::update(void) { }

void Heal::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < PLAYERINFOMANAGER->getViewDistance())
		_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
}

bool Heal::interact(Player* player)
{
	if (player == NULL)
	{
		destroyed = true;
		return true;
	}

	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setHeal(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}
	else return false;
}
