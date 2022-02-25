#include "Stdafx.h"
#include "Slime.h"

#include "Animation.h"
#include "Animator.h"

Slime::Slime() {}

HRESULT Slime::init(void)
{
	//! Do Nothing
	return S_OK;
}

HRESULT Slime::init(const char * imageName, POINT position)
{
	_worldTimeCount = TIMEMANAGER->getWorldTime();
	_rndTimeCount = RND->getFromFloatTo(0.04f, 0.1f);

	_bulletFireCount = TIMEMANAGER->getWorldTime();
	_rndFireCount = RND->getFromFloatTo(0.5f, 4.5f);
	turnCount = 0;
	count = 0;

	_image = IMAGEMANAGER->findImage(imageName);
	
	IMAGEMANAGER->addFrameImage(KEY_SLIME, DIR_SLIME, 208, 104, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_JUMP, DIR_SLIME_JUMP, 208, 82, 4, 1, 4, true, MAGENTA);
	
	pos = position;
	_rc = RectMakeCenter(position.x * TILE_SIZE + TILE_SIZE / 2, 
						 position.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);

	slimeJumpAnimator = new Animator();
	Animation* slimeJump = new Animation();

	slimeJump->init(
		KEY_SLIME_JUMP,
		POINT{ -26, -64 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	slimeJumpAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeJump);

	posCheck = true;

	return S_OK;
}

void Slime::release(void)
{
	SAFE_RELEASE(slimeJumpAnimator);
	SAFE_DELETE(slimeJumpAnimator);
}

void Slime::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	count++;
	move();

	slimeJumpAnimator->update();
}

void Slime::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}
	slimeJumpAnimator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}


void Slime::move(void)
{
}