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
	hp = 2;
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.
	// SlimeBlue.
	turnCount = 0;
	posCheck = true;

	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE, DIR_SLIME_BLUE, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP, DIR_SLIME_BLUE_JUMP, 208, 184, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP_TOP, DIR_SLIME_BLUE_JUMP_TOP, 208, 224, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP_BOTTOM, DIR_SLIME_BLUE_JUMP_BOTTOM, 208, 188, 4, 2, 4, true, MAGENTA);

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
}

bool SlimeBlue::interact(Player* player)
{
	hp--;
	if (hp <= 0) destroyed = true;
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

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
		if (turnCount >= 0.4f)
		{
			pos.y -= 1;

			animator->changeAnimation(CHARACTER_STATE::JUMP_TOP);

			turnCount -= 0.4f;
			posCheck = false;
		}
	}

	if (!posCheck)
	{
		if (turnCount >= 0.4f)
		{
			pos.y += 1;

			animator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);

			turnCount -= 0.4f;
			posCheck = true;
		}
	}

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
