#include "stdafx.h"
#include "slimeBlue.h"

#include "Animation.h"
#include "Animator.h"

HRESULT SlimeBlue::init(void)
{
	//! Do Nothing
	return S_OK;
}

HRESULT SlimeBlue::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);
	turnCount = 0;
	count = 0;

	_image = IMAGEMANAGER->findImage(imageName);

	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE, DIR_SLIME_BLUE, 208, 104, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP, DIR_SLIME_BLUE_JUMP, 208, 104, 4, 2, 8, true, MAGENTA);

	pos = position;
	_rc = RectMakeCenter(position.x * TILE_SIZE + TILE_SIZE / 2,
		position.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);

	slimeBlueJumpAnimator = new Animator();
	Animation* slimeJump = new Animation();

	slimeJump->init(
		KEY_SLIME_BLUE,
		POINT{ -26, -64 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	slimeBlueJumpAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeJump);

	posCheck = true;

	return S_OK;
}

void SlimeBlue::release(void)
{
	SAFE_RELEASE(slimeBlueJumpAnimator);
	SAFE_DELETE(slimeBlueJumpAnimator);
}

void SlimeBlue::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	count++;
	move();

	slimeBlueJumpAnimator->update();
}

void SlimeBlue::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	slimeBlueJumpAnimator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}

void SlimeBlue::move(void)
{
}

SlimeBlue::SlimeBlue()
{
}
