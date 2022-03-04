#include "Stdafx.h"

#include "Effect.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

HRESULT IceBlast::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EFFECT_ICEBLAST;
	animator = new Animator();
	scene = scenePtr;

	Animation* anim = new Animation();
	anim->init(
		KEY_EFFECT_ICEBLAST,
		POINT{ -176, -109 }, CHARACTER_STATE::IDLE_RIGHT,
		false, false, 32);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);

	return S_OK;
}

void IceBlast::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void IceBlast::update(void)
{
	if (animator->isEnd()) destroyed = true;
	animator->update();
}

void IceBlast::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	animator->animationRender(getMemDC(), renderPos);
}

bool IceBlast::interact(Player* player) { return true; }

IceBlast::IceBlast()
{
	pos = POINT{ 0, 0 };
	type = OBJECT_TYPE::EFFECT_ICEBLAST;
	animator = NULL;
}

IceBlast::~IceBlast() { release(); }

// Explosion55.
HRESULT Explosion55::init(Scene* scenePtr, POINT position)
{
	// GameNode.
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EFFECT_EXPLOSION55;
	animator = new Animator();
	scene = scenePtr;

	Animation* anim = new Animation();
	anim->init(
		KEY_EFFECT_EXPLOSION55,
		POINT{ -111, -111 }, CHARACTER_STATE::IDLE_RIGHT,
		false, false, 32);

	animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);

	return S_OK;
}

void Explosion55::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Explosion55::update(void)
{
	if (animator->isEnd()) destroyed = true;
	animator->update();
}

void Explosion55::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	animator->animationRender(getMemDC(), renderPos);
}

bool Explosion55::interact(Player* player) { return true; }

Explosion55::Explosion55()
{
	pos = POINT{ 0, 0 };
	type = OBJECT_TYPE::EFFECT_EXPLOSION55;
	animator = NULL;
}

Explosion55::~Explosion55() { release(); }
