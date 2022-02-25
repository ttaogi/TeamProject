#include "Stdafx.h"

#include "Player.h"

#include "Animation.h"
#include "Animator.h"

HRESULT Player::init(void)
{
	hp = 6;
	tileEmpty = true;
	initTime = TIMEMANAGER->getWorldTime();
	turnCount = 0;
	command = DIRECTION::DIRECTION_NUM;
	Move(POINT{ 0, 0 });

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_IDLE_RIGHT, DIR_PLAYER_HEAD_IDLE_RIGHT, 192, 96, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_IDLE_RIGHT, DIR_PLAYER_BODY_IDLE_RIGHT, 192, 28, 4, 1, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_IDLE_LEFT, DIR_PLAYER_HEAD_IDLE_LEFT, 192, 96, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_IDLE_LEFT, DIR_PLAYER_BODY_IDLE_LEFT, 192, 28, 4, 1, 4, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_RIGHT, DIR_PLAYER_HEAD_JUMP_RIGHT, 384, 144, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_RIGHT, DIR_PLAYER_BODY_JUMP_RIGHT, 384, 104, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_LEFT, DIR_PLAYER_HEAD_JUMP_LEFT, 384, 144, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_LEFT, DIR_PLAYER_BODY_JUMP_LEFT, 384, 104, 4, 2, 8, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_TOP, DIR_PLAYER_HEAD_JUMP_TOP, 192, 192, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_TOP, DIR_PLAYER_BODY_JUMP_TOP, 192, 152, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_HEAD_JUMP_BOTTOM, DIR_PLAYER_HEAD_JUMP_BOTTOM, 192, 192, 4, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_PLAYER_BODY_JUMP_BOTTOM, DIR_PLAYER_BODY_JUMP_BOTTOM, 192, 152, 4, 2, 8, true, MAGENTA);

	headAnimator = new Animator();
	bodyAnimator = new Animator();

	Animation* headIdleRight = new Animation();
	Animation* bodyIdleRight = new Animation();
	Animation* headJumpRight = new Animation();
	Animation* bodyJumpRight = new Animation();

	Animation* headIdleLeft = new Animation();
	Animation* bodyIdleLeft = new Animation();
	Animation* headJumpLeft = new Animation();
	Animation* bodyJumpLeft = new Animation();

	Animation* headJumpTop = new Animation();
	Animation* bodyJumpTop = new Animation();
	Animation* headJumpBottom = new Animation();
	Animation* bodyJumpBottom = new Animation();

	headIdleRight->init(
		KEY_PLAYER_HEAD_IDLE_RIGHT,
		POINT{ -24, -44 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);
	bodyIdleRight->init(
		KEY_PLAYER_BODY_IDLE_RIGHT,
		POINT{ -24, -24 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);
	headJumpRight->init(
		KEY_PLAYER_HEAD_JUMP_RIGHT,
		POINT{ -72, -68 }, CHARACTER_STATE::JUMP_RIGHT,
		false, false, 64
	);
	bodyJumpRight->init(
		KEY_PLAYER_BODY_JUMP_RIGHT,
		POINT{ -72, -48 }, CHARACTER_STATE::JUMP_RIGHT,
		false, false, 64
	);

	headIdleLeft->init(
		KEY_PLAYER_HEAD_IDLE_LEFT,
		POINT{ -24, -44 }, CHARACTER_STATE::IDLE_LEFT,
		true, false, 16
	);
	bodyIdleLeft->init(
		KEY_PLAYER_BODY_IDLE_LEFT,
		POINT{ -24, -24 }, CHARACTER_STATE::IDLE_LEFT,
		true, false, 16
	);
	headJumpLeft->init(
		KEY_PLAYER_HEAD_JUMP_LEFT,
		POINT{ -24, -68 }, CHARACTER_STATE::JUMP_LEFT,
		false, false, 64
	);
	bodyJumpLeft->init(
		KEY_PLAYER_BODY_JUMP_LEFT,
		POINT{ -24, -48 }, CHARACTER_STATE::JUMP_LEFT,
		false, false, 64
	);

	headJumpTop->init(
		KEY_PLAYER_HEAD_JUMP_TOP,
		POINT{ -24, -44 }, CHARACTER_STATE::JUMP_TOP,
		false, false, 64
	);
	bodyJumpTop->init(
		KEY_PLAYER_BODY_JUMP_TOP,
		POINT{ -24, -24 }, CHARACTER_STATE::JUMP_TOP,
		false, false, 64
	);
	headJumpBottom->init(
		KEY_PLAYER_HEAD_JUMP_BOTTOM,
		POINT{ -24, -92 }, CHARACTER_STATE::JUMP_BOTTOM,
		false, false, 64
	);
	bodyJumpBottom->init(
		KEY_PLAYER_BODY_JUMP_BOTTOM,
		POINT{ -24, -72 }, CHARACTER_STATE::JUMP_BOTTOM,
		false, false, 64
	);

	headAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, headIdleRight);
	bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, bodyIdleRight);
	headAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, headIdleLeft);
	bodyAnimator->addAnimation(CHARACTER_STATE::IDLE_LEFT, bodyIdleLeft);

	headAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, headJumpRight);
	bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_RIGHT, bodyJumpRight);
	headAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, headJumpLeft);
	bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_LEFT, bodyJumpLeft);

	headAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, headJumpTop);
	bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_TOP, bodyJumpTop);
	headAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, headJumpBottom);
	bodyAnimator->addAnimation(CHARACTER_STATE::JUMP_BOTTOM, bodyJumpBottom);

	return S_OK;
}

void Player::release(void)
{
	SAFE_RELEASE(headAnimator);
	SAFE_DELETE(headAnimator);
	SAFE_RELEASE(bodyAnimator);
	SAFE_DELETE(bodyAnimator);
}

void Player::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	if (headAnimator->isEnd())
	{
		if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_RIGHT)
			headAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
		if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_LEFT)
			headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
		if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_TOP)
			headAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
		if (headAnimator->getCurrentState() == CHARACTER_STATE::JUMP_BOTTOM)
			headAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
	}
	if (bodyAnimator->isEnd())
	{
		if(bodyAnimator->getCurrentState() == CHARACTER_STATE::JUMP_RIGHT)
			bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
		if (bodyAnimator->getCurrentState() == CHARACTER_STATE::JUMP_LEFT)
			bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
		if (bodyAnimator->getCurrentState() == CHARACTER_STATE::JUMP_TOP)
			bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);
		if (bodyAnimator->getCurrentState() == CHARACTER_STATE::JUMP_BOTTOM)
			bodyAnimator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
	}

	if (turnCount >= 0.4f && turnCount < 0.5f)
	{
		if (KEYMANAGER->isOnceKeyDown(VK_LEFT))
			command = DIRECTION::LEFT;
		else if(KEYMANAGER->isOnceKeyDown(VK_RIGHT))
			command = DIRECTION::RIGHT;
		else if(KEYMANAGER->isOnceKeyDown(VK_UP))
			command = DIRECTION::TOP;
		else if(KEYMANAGER->isOnceKeyDown(VK_DOWN))
			command = DIRECTION::BOTTOM;
	}
	else if (turnCount >= 0.5f)
	{
		turnCount -= 0.5f;
		switch (command) {
		case DIRECTION::LEFT:
			Move(POINT{ pos.x - 1, pos.y });
			headAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
			bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_LEFT);
			break;
		case DIRECTION::RIGHT:
			Move(POINT{ pos.x + 1, pos.y });
			headAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
			bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_RIGHT);
			break;
		case DIRECTION::TOP:
			Move(POINT{ pos.x, pos.y - 1 });
			headAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
			bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_TOP);
			break;
		case DIRECTION::BOTTOM:
			Move(POINT{ pos.x, pos.y + 1 });
			headAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
			bodyAnimator->changeAnimation(CHARACTER_STATE::JUMP_BOTTOM);
			break;
		}
		command = DIRECTION::DIRECTION_NUM;
	}

	headAnimator->update();
	bodyAnimator->update();
}

void Player::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
	{
		Rectangle(getMemDC(), rc.left, rc.top, rc.right, rc.bottom);
	}

	headAnimator->animationRender(getMemDC(), GripPointToPixelPointCenter(pos));
	bodyAnimator->animationRender(getMemDC(), GripPointToPixelPointCenter(pos));

	if(turnCount >= 0.4f)
		RectangleMake(getMemDC(), 0, 0, 100, 100);

}

void Player::Move(POINT _pos)
{
	pos = _pos;
	rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
						pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
