#include "stdafx.h"

#include "Head.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT Head::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_HEAD;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::HEAD);

	return S_OK;
}

void Head::release(void) { }

void Head::update(void) { }

void Head::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
}

bool Head::interact(Player * player)
{
	if (player == NULL)
	{
		destroyed = true;
		return true;
	}

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
