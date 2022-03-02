#include "stdafx.h"

#include "Attack.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT Dagger::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_ATTACK_DAGGER;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::ATTACK_DAGGER);

	return S_OK;
}

void Dagger::release(void)
{
}

void Dagger::update(void)
{
}

void Dagger::render(void)
{
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool Dagger::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setAttack(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}

//==================================================================
HRESULT BroadSword::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_ATTACK_BROADSWORD;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::ATTACK_BROADSWORD);

	return S_OK;
}

void BroadSword::release(void)
{
}

void BroadSword::update(void)
{
}

void BroadSword::render(void)
{
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool BroadSword::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setAttack(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}
