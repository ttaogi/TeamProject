#include "stdafx.h"

#include "Bat.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Bat::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_BAT;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = 2;
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.
	// SlimeBlue.
	turnCount = 0;
	posCheck = true;
	rightCount = 0;
	leftCount = 0;

	IMAGEMANAGER->addFrameImage(KEY_BAT_LEFT, DIR_BAT_LEFT, 288, 96, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_BAT_RIGHT, DIR_BAT_RIGHT, 288, 96, 4, 2, 4, true, MAGENTA);

	Animation* batLeft = new Animation();
	batLeft->init(
		KEY_BAT_LEFT,
		POINT{ -37, -50 }, CHARACTER_STATE::IDLE_LEFT,
		true, false, 16
	);

	Animation* batRight = new Animation();
	batRight->init(
		KEY_BAT_RIGHT,
		POINT{ -37, -50 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	animator->addAnimation(CHARACTER_STATE::IDLE_LEFT, batLeft);
	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, batRight);

	return S_OK;
}

void Bat::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Bat::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	move();

	animator->update();
}

void Bat::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	animator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}

bool Bat::interact(Player* player)
{
	hp--;
	if (hp <= 0) destroyed = true;
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

	return false;
}

void Bat::move(void)
{
	if (animator->isEnd())
	{
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}

	if (posCheck)
	{
		if (turnCount >= 0.4f)
		{
			pos.x += 1;
			animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			turnCount -= 0.4f;
		
			rightCount++;

			if(rightCount == 3)
			{
				leftCount = 0;
				posCheck = false;
			}
		}
	}

	if (!posCheck)
	{
		if (turnCount >= 0.4f)
		{
			pos.x -= 1;

			animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			
			turnCount -= 0.4f;

			leftCount++;
			if (leftCount == 3)
			{
				rightCount = 0;
				posCheck = true;
			}
		}
	}

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}