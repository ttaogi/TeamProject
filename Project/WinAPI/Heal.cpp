#include "stdafx.h"

#include "Heal.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

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

void Heal::release(void)
{
}

void Heal::update(void)
{
}

void Heal::render(void)
{
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool Heal::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setHead(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}
