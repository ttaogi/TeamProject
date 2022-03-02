#include "stdafx.h"

#include "Body.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT Body::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_BOBY;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::BODY);

	return S_OK;
}

void Body::release(void)
{
}

void Body::update(void)
{
}

void Body::render(void)
{
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool Body::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setBody(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}
