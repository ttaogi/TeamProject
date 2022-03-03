#include "stdafx.h"

#include "Necrodancer.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Necrodancer::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_NECRODANCER;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = 6;
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.

	turnCount = 0;
	
	posCheck = true;
	rightIdleTF = true;
	leftIdleTF = false;

	rightUpJump = false;
	rightDownJump = false;

	leftUpJump = false;
	leftDownJump = false;

	explosion = false;

	countTF = false;
	countTF2 = false;

	rightCount = 0;
	leftCount = 0;

	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_IDLE, DIR_NECRODANCER_RIGHT_IDLE, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_UP_JUMP, DIR_NECRODANCER_RIGHT_UP_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_DOWN_JUMP, DIR_NECRODANCER_RIGHT_DOWN_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_IDLE, DIR_NECRODANCER_LEFT_IDLE, 352, 212, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_UP_JUMP, DIR_NECRODANCER_LEFT_UP_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_DOWN_JUMP, DIR_NECRODANCER_LEFT_DOWN_JUMP, 704, 286, 4, 2, 4, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_EXPLOSION_IDLE, DIR_NECRODANCER_EXPLOSION_IDLE, 88, 212, 1, 2, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_EXPLOSION, DIR_NECRODANCER_EXPLOSION, 440, 212, 5, 2, 5, true, MAGENTA);
	
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_RIGHT_BLUEATT, DIR_NECRODANCER_RIGHT_BLUEATT, 88, 212, 1, 2, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_LEFT_BLUEATT, DIR_NECRODANCER_LEFT_BLUEATT, 88, 212, 1, 2, 1, true, MAGENTA);

	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_SOHWAN_IDLE, DIR_NECRODANCER_SOHWAN_IDLE, 88, 212, 1, 2, 1, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_NECRODANCER_IDLE2, DIR_NECRODANCER_IDLE2, 176, 212, 2, 2, 2, true, MAGENTA);


	Animation* necrodancerRightIdle = new Animation();
	necrodancerRightIdle->init(
		KEY_NECRODANCER_RIGHT_IDLE,
		POINT{ -45, -100 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	Animation* necrodancerRightUpJump = new Animation();
	necrodancerRightUpJump->init(
		KEY_NECRODANCER_RIGHT_UP_JUMP,
		POINT{ -90, -90 }, CHARACTER_STATE::RIGHT_UP_JUMP,
		false, false, 16
	);

	Animation* necrodancerRightDownJump = new Animation();
	necrodancerRightDownJump->init(
		KEY_NECRODANCER_RIGHT_DOWN_JUMP,
		POINT{ -90, -140 }, CHARACTER_STATE::RIGHT_DOWN_JUMP,
		false, false, 16
	);

	Animation* necrodancerLeftIdle = new Animation();
	necrodancerLeftIdle->init(
		KEY_NECRODANCER_LEFT_IDLE,
		POINT{ -43, -100 }, CHARACTER_STATE::IDLE_LEFT,
		true, false, 16
	);

	Animation* necrodancerLeftUpJump = new Animation();
	necrodancerLeftUpJump->init(
		KEY_NECRODANCER_LEFT_UP_JUMP,
		POINT{ -90, -90 }, CHARACTER_STATE::LEFT_UP_JUMP,
		false, false, 16
	);

	Animation* necrodancerLeftDownJump = new Animation();
	necrodancerLeftDownJump->init(
		KEY_NECRODANCER_LEFT_DOWN_JUMP,
		POINT{ -85, -140 }, CHARACTER_STATE::LEFT_DOWN_JUMP,
		false, false, 16
	);

	Animation* necrodancerExplosionIdle = new Animation();
	necrodancerExplosionIdle->init(
		KEY_NECRODANCER_EXPLOSION_IDLE,
		POINT{ -45, -100 }, CHARACTER_STATE::EXPLOSION_IDLE,
		false, false, 16
	);

	Animation* necrodancerExplosion = new Animation();
	necrodancerExplosion->init(
		KEY_NECRODANCER_EXPLOSION,
		POINT{ -45, -100 }, CHARACTER_STATE::EXPLOSION,
		false, false, 16
	);

	Animation* necrodancerRightBuleATT = new Animation();
	necrodancerRightBuleATT->init(
		KEY_NECRODANCER_RIGHT_BLUEATT,
		POINT{ -45, -100 }, CHARACTER_STATE::RIGHT_BLUEATT,
		true, false, 16
	);

	Animation* necrodancerLeftBuleATT = new Animation();
	necrodancerLeftBuleATT->init(
		KEY_NECRODANCER_LEFT_BLUEATT,
		POINT{ -42, -100 }, CHARACTER_STATE::LEFT_BLUEATT,
		true, false, 16
	);

	Animation* necrodancerSohwanIdle = new Animation();
	necrodancerSohwanIdle->init(
		KEY_NECRODANCER_SOHWAN_IDLE,
		POINT{ -45, -100 }, CHARACTER_STATE::SOHWAN_IDLE,
		true, false, 16
	);

	Animation* necrodancerIdle2 = new Animation();
	necrodancerIdle2->init(
		KEY_NECRODANCER_IDLE2,
		POINT{ -45, -100 }, CHARACTER_STATE::IDLE2,
		true, false, 16
	);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, necrodancerRightIdle);
	animator->addAnimation(CHARACTER_STATE::RIGHT_UP_JUMP, necrodancerRightUpJump);
	animator->addAnimation(CHARACTER_STATE::RIGHT_DOWN_JUMP, necrodancerRightDownJump);

	animator->addAnimation(CHARACTER_STATE::IDLE_LEFT, necrodancerLeftIdle);
	animator->addAnimation(CHARACTER_STATE::LEFT_UP_JUMP, necrodancerLeftUpJump);
	animator->addAnimation(CHARACTER_STATE::LEFT_DOWN_JUMP, necrodancerLeftDownJump);

	animator->addAnimation(CHARACTER_STATE::EXPLOSION_IDLE, necrodancerExplosionIdle);
	animator->addAnimation(CHARACTER_STATE::EXPLOSION, necrodancerExplosion);

	animator->addAnimation(CHARACTER_STATE::RIGHT_BLUEATT, necrodancerRightBuleATT);
	animator->addAnimation(CHARACTER_STATE::LEFT_BLUEATT, necrodancerLeftBuleATT);

	animator->addAnimation(CHARACTER_STATE::SOHWAN_IDLE, necrodancerSohwanIdle);
	animator->addAnimation(CHARACTER_STATE::IDLE2, necrodancerIdle2);

	return S_OK;
}

void Necrodancer::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Necrodancer::update(void)
{
	if (countTF)
	{
		turnCount += TIMEMANAGER->getElapsedTime();
	}

	move();

	animator->update();
}

void Necrodancer::render(void)
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

bool Necrodancer::interact(Player* player)
{
	if (player)
	{
		hp--;
	}
	else
	{
		hp -= 4;
	}

	if (hp <= 0)
	{
		Object* obj = NULL;
		for (int i = 6; i <= 10; ++i)
		{
			obj = NULL;
			obj = scene->getObject(POINT{ i, 5 });
			if (obj)
				obj->setDestroyed(true);
		}
		destroyed = true;
	}
	
	return false;
}

void Necrodancer::move(void)
{
	if (animator->isEnd())
	{
		if(rightIdleTF && !leftIdleTF)
		animator->changeAnimation(CHARACTER_STATE::IDLE_RIGHT);

		else if (leftIdleTF && !rightIdleTF)
		animator->changeAnimation(CHARACTER_STATE::IDLE_LEFT);
	}

	else if (rightUpJump)
	{
		pos.x += 1;
		pos.y -= 1;
		animator->changeAnimation(CHARACTER_STATE::RIGHT_UP_JUMP);
		rightUpJump = false;

		rightIdleTF = false;
		leftIdleTF = true;
	}

	else if (rightDownJump)
	{
		pos.x += 1;
		pos.y += 1;
		animator->changeAnimation(CHARACTER_STATE::EXPLOSION);
		rightDownJump = false;
		
		rightIdleTF = false;
		leftIdleTF = true;
	}

	else if (leftUpJump)
	{
		pos.x -= 1;
		pos.y -= 1;
		animator->changeAnimation(CHARACTER_STATE::LEFT_UP_JUMP);
		leftUpJump = false;

		rightIdleTF = true;
		leftIdleTF = false;
	}

	else if (leftDownJump)
	{
		pos.x -= 1;
		pos.y += 1;
		animator->changeAnimation(CHARACTER_STATE::LEFT_DOWN_JUMP);
		leftDownJump = false;

		rightIdleTF = true;
		leftIdleTF = false;
	}

	else if (explosion)
	{
		animator->changeAnimation(CHARACTER_STATE::EXPLOSION);	
		explosion = false;
	}

	if (turnCount >= 0.5f)
	{
		animator->changeAnimation(CHARACTER_STATE::EXPLOSION);
		
		pos.x -= 5;
		pos.y += 2;
		
		rightIdleTF = false;
		leftIdleTF = true;
		turnCount -= 0.5f;
		countTF = false;
	}

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
