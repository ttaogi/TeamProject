#include "Stdafx.h"

#include "Wall.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Wall::init(OBJECT_TYPE _type, POINT _pos, Scene* _scenPtr)
{
	destroyed = false;
	type = _type;
	pos = _pos;
	scene = _scenPtr;
	
	Animation* anim = NULL;

	switch (_type)
	{
	case OBJECT_TYPE::WALL_UNBREAKABLE:
		hp = INT_MAX;
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
		hp = 1;
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
		hp = INT_MAX;
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
		return E_FAIL;
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
	if (animator && !destroyed)
		animator->update();
}

void Wall::render(void)
{
	POINT renderPos = GridPointToPixelPointCenter(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	
	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < 8)
	{
		if (animator && !destroyed)
		{
			animator->animationRender(getMemDC(), renderPos);
		}
	}
	

}

bool Wall::interact(Player* player)
{
	hp--;
	if (hp <= 0) destroyed = true;

	return false;
}

Wall::Wall() {
	type = OBJECT_TYPE::NONE;
	pos = POINT{ 0, 0 };
	animator = NULL;
}

Wall::~Wall() { release(); }
