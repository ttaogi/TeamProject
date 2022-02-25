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

	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE, DIR_SLIME_BLUE, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_BLUE_JUMP, DIR_SLIME_BLUE_JUMP, 208, 184, 4, 2, 4, true, MAGENTA);

	pos = position;
	_rc = RectMakeCenter(position.x * TILE_SIZE + TILE_SIZE / 2,
						 position.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);


	slimeBlueAnimator = new Animator();
	Animation* slimeBlue = new Animation();
	slimeBlue->init(
		KEY_SLIME_BLUE,
		POINT{ -26, -50 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	Animation* slimeBlueJump = new Animation();
	slimeBlueJump->init(
		KEY_SLIME_BLUE_JUMP,
		POINT{ -26, -90 }, CHARACTER_STATE::JUMP_TOP,
		false, false, 64
	);

	slimeBlueAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeBlue);
	slimeBlueAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, slimeBlueJump);

	posCheck = true;

	return S_OK;
}

void SlimeBlue::release(void)
{
	SAFE_RELEASE(slimeBlueAnimator);
	SAFE_DELETE(slimeBlueAnimator);
}

void SlimeBlue::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();
	
	move();

	slimeBlueAnimator->update();
}

void SlimeBlue::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

	slimeBlueAnimator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}

void SlimeBlue::move(void)
{
	if (slimeBlueAnimator->isEnd())
	{
		slimeBlueAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
	}
	
	if (posCheck)
	{
		if (turnCount >= 0.4f)
		{
			pos.y -= 1;

			slimeBlueAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
			//변수의 위치를바꿔주고 동시에 애니메이션을 바꿔준다고?
			//슬라임 블루 애니메이터->체인지애니매이션 이런 함수가 있을꺼야
			//값을 탑으로 바꿔주던가...

			turnCount -= 0.4f;
			posCheck = false;
		}
	}

	if (!posCheck)
	{
		if (turnCount >= 0.4f)
		{
			pos.y += 1;

			slimeBlueAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);

			turnCount -= 0.4f;
			posCheck = true;
		}
	}




	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);

}

SlimeBlue::SlimeBlue()
{
}
