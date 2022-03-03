#include "stdafx.h"

#include "slimeBlue.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT SlimeBlue::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_SLIME_BLUE;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = hpMax = 2;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.
	// SlimeBlue.
	turnCount = 0;
	posCheck = true;

	Animation* slimeBlue = new Animation();
	slimeBlue->init(
		KEY_SLIME_BLUE,
		POINT{ -26, -50 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	Animation* slimeBlueJumpTop = new Animation();
	slimeBlueJumpTop->init(
		KEY_SLIME_BLUE_JUMP_TOP,
		POINT{ -26, -50 }, CHARACTER_STATE::JUMP_TOP,
		false, false, 64
	);

	Animation* slimeBlueJumpBottom = new Animation();
	slimeBlueJumpBottom->init(
		KEY_SLIME_BLUE_JUMP_BOTTOM,
		POINT{ -26, -100 }, CHARACTER_STATE::JUMP_BOTTOM,
		false, false, 64
	);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeBlue);
	animator->addAnimation(CHARACTER_STATE::JUMP_TOP, slimeBlueJumpTop);
	animator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, slimeBlueJumpBottom);

	return S_OK;
}

void SlimeBlue::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void SlimeBlue::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	
	move();

	animator->update();
}

void SlimeBlue::render(void)
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

bool SlimeBlue::interact(Player* player)
{
	if (player)	hp--;
	else		hp -= 4;

	if (hp <= 0) destroyed = true;

	return false;
}

void SlimeBlue::move(void)
{
	if (animator->isEnd())
	{
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}
	
	if (posCheck)
	{
		if (turnCount >= turnInterval)
		{
			pos.y -= 1;

			animator->changeAnimation(CHARACTER_STATE::JUMP_TOP);

			turnCount -= turnInterval;
			posCheck = false;
		}
	}

	if (!posCheck)
	{
		if (turnCount >= turnInterval)
		{
			pos.y += 1;

			animator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);

			turnCount -= turnInterval;
			posCheck = true;
		}
	}

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
