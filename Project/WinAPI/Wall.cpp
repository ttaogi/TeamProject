#include "Stdafx.h"

#include "Wall.h"

#include "Animation.h"
#include "Animator.h"

HRESULT Wall::init(OBJECT_TYPE _type, POINT _pos)
{
	type = _type;
	pos = _pos;

	Animation* anim = NULL;

	switch (_type)
	{
	case OBJECT_TYPE::WALL_UNBREAKABLE:
		animator = new Animator();
		animator->init();
		anim = new Animation();
		anim->init(
			KEY_WALL_UNBREAKABLE,
			POINT{ TILE_SIZE / -2, TILE_SIZE * -1 },
			CHARACTER_STATE::IDLE_RIGHT, false, false, 1
		);
		animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);
		animator->aniPause();
		break;
	case OBJECT_TYPE::WALL_DIRT:
		animator = new Animator();
		animator->init();
		anim = new Animation();
		anim->init(
			KEY_WALL_DIRT,
			POINT{ TILE_SIZE / -2, TILE_SIZE * -1 },
			CHARACTER_STATE::IDLE_RIGHT, false, false, 1
		);
		anim->setFrameIdx(RND->getInt(
			IMAGEMANAGER->findImage(KEY_WALL_DIRT)->getMaxFrameIdx()));
		animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);
		animator->aniPause();
		break;
	case OBJECT_TYPE::WALL_SHOP:
		animator = new Animator();
		animator->init();
		anim = new Animation();
		anim->init(
			KEY_WALL_SHOP,
			POINT{ TILE_SIZE / -2, TILE_SIZE * -1 },
			CHARACTER_STATE::IDLE_RIGHT, false, false, 1
		);
		animator->addAnimation(CHARACTER_STATE::IDLE_RIGHT, anim);
		animator->aniPause();
		break;
	case OBJECT_TYPE::NONE:
	default:
		animator = NULL;
		break;
	}

	return S_OK;
}

void Wall::release(void)
{
	SAFE_RELEASE(animator);
	SAFE_DELETE(animator);
}

void Wall::update(void)
{
	if (animator)
		animator->update();
}

void Wall::render(void)
{
	POINT p = GripPointToPixelPointCenter(pos);
	if (animator)
		animator->animationRender(getMemDC(), p);
}

Wall::Wall() {
	type = OBJECT_TYPE::NONE;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

Wall::~Wall() { release(); }
