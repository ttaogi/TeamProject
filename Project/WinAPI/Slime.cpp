#include "Stdafx.h"

#include "Slime.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Slime::init(Scene* scenePtr, POINT position)
{
	// object.
	destroyed = false;
	type = OBJECT_TYPE::MONSTER_SLIME;
	animator = new Animator();
	scene = scenePtr;
	// enemy.
	hp = 1;
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	move(position); // set pos(gameNode) and _rc.
	
	IMAGEMANAGER->addFrameImage(KEY_SLIME, DIR_SLIME, 208, 104, 4, 2, 4, true, MAGENTA);
	IMAGEMANAGER->addFrameImage(KEY_SLIME_JUMP, DIR_SLIME_JUMP, 208, 164, 4, 2, 4, true, MAGENTA);

	Animation* slimeJump = new Animation();
	slimeJump->init(
		KEY_SLIME_JUMP,
		POINT{ -26, -80 }, CHARACTER_STATE::IDLE_RIGHT, // change jump state.
		true, false, 16
	);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, slimeJump); // change jump state.

	return S_OK;
}

void Slime::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Slime::update(void)
{
	animator->update();
}

void Slime::render(void)
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

bool Slime::interact(Player* player)
{
	if (player)
	{
		hp--;
	}

	else
	{
		hp -= 4;
	}

	if (hp <= 0) destroyed = true;

	return false;
}
