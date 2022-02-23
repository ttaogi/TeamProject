#include "Stdafx.h"

#include "Player.h"

HRESULT Player::init(void)
{
	hp = 6;
	initTime = TIMEMANAGER->getWorldTime();
	turnCount = 0;
	command = DIRECTION::DIRECTION_NUM;
	Move(POINT{ 0, 0 });
	body = IMAGEMANAGER->addImage(KEY_PLAYER_TMP, DIR_PLAYER_TMP, 48, 48, true, MAGENTA);

	return S_OK;
}

void Player::release(void)
{
}

void Player::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

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
			break;
		case DIRECTION::RIGHT:
			Move(POINT{ pos.x + 1, pos.y });
			break;
		case DIRECTION::TOP:
			Move(POINT{ pos.x, pos.y - 1 });
			break;
		case DIRECTION::BOTTOM:
			Move(POINT{ pos.x, pos.y + 1 });
			break;
		}
		command = DIRECTION::DIRECTION_NUM;
	}
}

void Player::render(void)
{
	body->render(getMemDC(), rc.left, rc.top);
	if(turnCount >= 0.4f)
		RectangleMake(getMemDC(), 0, 0, 100, 100);
}

void Player::Move(POINT _pos)
{
	pos = _pos;
	rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
