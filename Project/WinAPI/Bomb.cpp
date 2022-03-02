#include "stdafx.h"

#include "Bomb.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT Bomb::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::ITEM_BOMB;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::BOMB);

	return S_OK;
}

void Bomb::release(void)
{
}

void Bomb::update(void)
{
}

void Bomb::render(void)
{
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool Bomb::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setBomb(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}
