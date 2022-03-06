#include "stdafx.h"

#include "Explosion.h"
#include "Bomb.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Explosion::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::ITEM_BOMB;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::BOMB);
	sound = false;

	bombAnimator = new Animator();
	explosionAnimator = new Animator();
	
	Animation* bombAnimation = new Animation();
	Animation* explosionAnimation = new Animation();

	bombAnimation->init(KEY_ITEM_BOMBDROP, POINT{-24, -24}, CHARACTER_STATE::IDLE_RIGHT, false, false, 5);
	explosionAnimation->init(KEY_SFX_EXPLOSION, POINT{-74, -74}, CHARACTER_STATE::IDLE_RIGHT, false, false, 30);

	bombAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, bombAnimation);
	explosionAnimator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, explosionAnimation);
	
	return S_OK;
}

void Explosion::release(void)
{
	SAFE_RELEASE(bombAnimator);
	SAFE_DELETE(bombAnimator);
	SAFE_RELEASE(explosionAnimator);
	SAFE_DELETE(explosionAnimator);
}

void Explosion::update(void)
{
	if (!bombAnimator->isEnd())	bombAnimator->update();
	else
	{
		explosionAnimator->update();
		if (sound == false)
		{
			sound = true;
			SOUNDMANAGER->play(KEY_SFX_BOMB_EXPLODE, DEFAULT_VOLUME);
		}
	}
	

	if (explosionAnimator->isEnd())
	{
		for (int i = -1; i < 2; i++)
			for (int j = -1; j < 2; j++)
			{
				POINT p = pos;
				p.x += i;
				p.y += j;
				Object* obj = scene->getObject(p);
		
				if (obj) obj->interact(NULL);
			}
		
		destroyed = true;
	}
}

void Explosion::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	if (!bombAnimator->isEnd())
		bombAnimator->animationRender(getMemDC(), renderPos);
	else
		explosionAnimator->animationRender(getMemDC(), renderPos);
}