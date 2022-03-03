#include "stdafx.h"

#include "Attack.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"


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
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
}

bool Dagger::interact(Player * player)
{
	if (player == NULL)
	{
		destroyed = true;
		return true;
	}

	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		if(PLAYERINFOMANAGER->getAttack().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
		{
			Item tmp = PLAYERINFOMANAGER->getAttack();
			
			if(tmp.detailType == ITEM_DETAIL::ATTACK_DAGGER)
			{
				Dagger* _Object = new Dagger;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				BroadSword* _Object = new BroadSword;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_GOLDENLUTE)
			{
				Goldenlute* _Object = new Goldenlute;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}
		}
		
		PLAYERINFOMANAGER->setAttack(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;

		return true;
	}

	else return false;
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
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
}

bool BroadSword::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		if (PLAYERINFOMANAGER->getAttack().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
		{
			Item tmp = PLAYERINFOMANAGER->getAttack();

			if (tmp.detailType == ITEM_DETAIL::ATTACK_DAGGER)
			{
				Dagger* _Object = new Dagger;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				BroadSword* _Object = new BroadSword;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_GOLDENLUTE)
			{
				Goldenlute* _Object = new Goldenlute;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}
		}

		PLAYERINFOMANAGER->setAttack(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;

		return true;
	}

	else return false;
}

HRESULT Goldenlute::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_ATTACK_GOLDENLUTE;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::ATTACK_GOLDENLUTE);
	return S_OK;
}

void Goldenlute::release(void)
{
}

void Goldenlute::update(void)
{
}

void Goldenlute::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
}

bool Goldenlute::interact(Player * player)
{
	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		if (PLAYERINFOMANAGER->getAttack().detailType != ITEM_DETAIL::ITEM_DETAIL_NUM)
		{
			Item tmp = PLAYERINFOMANAGER->getAttack();

			if (tmp.detailType == ITEM_DETAIL::ATTACK_DAGGER)
			{
				Dagger* _Object = new Dagger;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_BROADSWORD)
			{
				BroadSword* _Object = new BroadSword;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}

			else if (tmp.detailType == ITEM_DETAIL::ATTACK_GOLDENLUTE)
			{
				Goldenlute* _Object = new Goldenlute;
				_Object->init(scene, pos);
				scene->getObjectVec()->push_back(_Object);
			}
		}

		PLAYERINFOMANAGER->setAttack(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;

		return true;
	}

	else return false;
}
