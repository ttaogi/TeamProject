#include "Stdafx.h"

#include "Money.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT Money::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::ITEM_MONEY;
	animator = new Animator();
	scene = scenePtr;
	// Money.
	quantity = 1;

	Animation* anim = new Animation();
	anim->init(
		KEY_ITEM_GOLD,
		POINT{ -24,-24 }, CHARACTER_STATE::IDLE_RIGHT,
		false, false, DEFAULT_FPS);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);
	animator->aniPause();

	setQuantity(1);

	return S_OK;
}

void Money::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Money::update(void) { }

void Money::render(void)
{
	POINT p = GridPointToPixelPointCenter(pos);
	animator->animationRender(getMemDC(), p);
}

bool Money::interact(Player* player)
{
	PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() + quantity);
	destroyed = true;

	return true;
}

void Money::setQuantity(int quan)
{
	quantity = quan;
	if(animator)
	{
		if (quan < 10)
			animator->setFrameIdx(quan - 1);
		else
			animator->setFrameIdx(9);
	}
}

Money::Money()
{
	type = OBJECT_TYPE::ITEM_MONEY;
	pos = POINT{ 0, 0 };
	animator = NULL;
	quantity = 0;
}

Money::~Money() { release(); }
