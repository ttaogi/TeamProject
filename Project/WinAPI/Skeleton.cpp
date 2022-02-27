#include "stdafx.h"

#include "Skeleton.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Skeleton::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_SKELETON;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = 1;
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	Enemy::move(position); // set pos(gameNode) and _rc.
	// SlimeBlue.
	turnCount = 0;
	posCheck = true;

	IMAGEMANAGER->addFrameImage(KEY_SKELETON_LEFT, DIR_SKELETON_LEFT, 384, 100, 8, 2, 8, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SKELETON_RIGHT, DIR_SKELETON_RIGHT, 384, 100, 8, 2, 8, true, MAGENTA);

	Animation* skeletonRight = new Animation();
	skeletonRight->init(
		KEY_SKELETON_RIGHT,
		POINT{ -23, -50 }, CHARACTER_STATE::IDLE_RIGHT,
		true, false, 16
	);

	Animation* skeletonLeft = new Animation();
	skeletonLeft->init(
		KEY_SKELETON_LEFT,
		POINT{ -23, -50 }, CHARACTER_STATE::IDLE_LEFT,
		true, false, 16
	);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, skeletonRight);
	animator->addAnimation(CHARACTER_STATE::IDLE_LEFT, skeletonLeft);

	return S_OK;
}

void Skeleton::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Skeleton::update(void)
{
	turnCount += TIMEMANAGER->getElapsedTime();

	move();

	animator->update();
}

void Skeleton::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	animator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}

bool Skeleton::interact(Player* player)
{
	hp--;
	if (hp <= 0) destroyed = true;
	{
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);
	}

	return false;
}

void Skeleton::move(void)
{
	//pos.x += 1;

	_rc = RectMakeCenter(pos.x * TILE_SIZE + TILE_SIZE / 2,
		pos.y * TILE_SIZE + TILE_SIZE / 2, TILE_SIZE, TILE_SIZE);
}
