#include "stdafx.h"

#include "Skeleton.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Skeleton::init(Scene* scenePtr, POINT position)
{
	/*_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);
	turnCount = 0;

	_image = IMAGEMANAGER->findImage(imageName);

	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE, DIR_SLIME_BLUE, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP, DIR_SLIME_BLUE_JUMP, 208, 184, 4, 2, 4, true, MAGENTA);

	pos = position;
	_rc = RectMakeCenter(position.x * TILE_SIZE + TILE_SIZE / 2,
		position.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);*/


	/*slimeBlueAnimator = new Animator();
	Animation* slimeBlue = new Animation();
	slimeBlue->init(
		KEY_SLIME_BLUE,
		POINT{ -26, -50 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);


	slimeBlueJumpAnimator = new Animator();
	Animation* slimeBlueJump = new Animation();
	slimeBlueJump->init(
		KEY_SLIME_BLUE_JUMP,
		POINT{ -26, -90 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	slimeBlueAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeBlue);
	slimeBlueJumpAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeBlueJump);

	posCheck = true;*/

	return S_OK;
}

void Skeleton::release(void)
{/*
	SAFE_RELEASE(slimeBlueAnimator);
	SAFE_DELETE(slimeBlueAnimator);
	SAFE_RELEASE(slimeBlueJumpAnimator);
	SAFE_DELETE(slimeBlueJumpAnimator);*/
}

void Skeleton::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	move();/*

	slimeBlueAnimator->update();
	slimeBlueJumpAnimator->update();*/
}

void Skeleton::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}/*

	slimeBlueAnimator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));*/
}

bool Skeleton::interact(Player * player)
{
	return false;
}

void Skeleton::move(void)
{
	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);

}
