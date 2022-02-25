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
	move(position); // set pos(gameNode) and _rc.
	// SlimeBlue.
	turnCount = 0;
	count = 0;
	posCheck = true;

	return S_OK;
}

void SlimeBlue::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void SlimeBlue::update(void)
{
}

void SlimeBlue::render(void)
{
	if (KEYMANAGER->isToggleKey(VK_F1))
		Rectangle(getMemDC(), _rc.left, _rc.top, _rc.right, _rc.bottom);

	animator->animationRender(getMemDC(), GridPointToPixelPointCenter(pos));
}

bool SlimeBlue::interact(Player* player)
{
	hp--;
	if (hp <= 0) destroyed = true;

	return false;
}
