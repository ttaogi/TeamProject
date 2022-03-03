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
	hp = hpMax = 1;
	turnInterval = scene->getMapInfo()->getTurnInterval();
	_rc = RECT{ 0, 0, TILE_SIZE, TILE_SIZE };
	move(position); // set pos(gameNode) and _rc.

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

	int count = hp;
	if (hp != hpMax)
		for (int i = 0; i < hpMax; ++i)
		{
			if (count >= 1)
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_FULL)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			else
				IMAGEMANAGER->findImage(KEY_UI_MONSTER_HEART_EMPTY)->
				render(getMemDC(), renderPos.x - 48 + i * 24, renderPos.y - 78);
			--count;
		}
}

bool Slime::interact(Player* player)
{
	if (player)	hp--;
	else		hp -= 4;

	if (hp <= 0) destroyed = true;

	return false;
}
