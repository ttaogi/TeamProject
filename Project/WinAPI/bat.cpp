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
	hp = hpMax = 4;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.

	turnCount = 0;
	posCheck = true;
	rightCount = 0;
	leftCount = 0;

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
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(),
			_rc.left - revision.x, _rc.top - revision.y,
			_rc.right - revision.x, _rc.bottom - revision.y);

	animator->animationRender(getMemDC(), renderPos);

	int count = hp;
	if (hp != hpMax)
		for (int i = 0; i < hpMax; ++i)
		{
			if (count >= 1)
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_FULL)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			else
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_EMPTY)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			--count;
		}
}

bool Bat::interact(Player* player)
{
	if (player)	hp--;
	else		hp -= 4;

	if (hp <= 0) destroyed = true;

	return false;
}

void Bat::move(void)
{
	if (animator->isEnd())
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);

	if (posCheck)
	{
		if (turnCount >= turnInterval)
		{
			pos.x += 1;
			animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
			turnCount -= turnInterval;
		
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
		if (turnCount >= turnInterval)
		{
			pos.x -= 1;

			animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
			
			turnCount -= turnInterval;

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
