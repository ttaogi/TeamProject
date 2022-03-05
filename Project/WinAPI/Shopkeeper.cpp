#include "stdafx.h"

#include "Shopkeeper.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"

HRESULT Shopkeeper::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::NPC_SHOP;
	animator = NULL;
	scene = scenePtr;
	
	shopkeeper = new Animator();

	Animation* shopkeeperAnimation = new Animation();

	shopkeeperAnimation->init(KEY_NPC_SHOPKEEPER, POINT{ -24, -35 }, CHARACTER_STATE::IDLE_RIGHT, true, false, 10);
	shopkeeper->addAnimation(CHARACTER_STATE::IDLE_RIGHT, shopkeeperAnimation);

	return S_OK;
}

void Shopkeeper::release(void)
{
	SAFE_RELEASE(shopkeeper);
	SAFE_DELETE(shopkeeper);
}

void Shopkeeper::update(void)
{	
	shopkeeper->update();
}

void Shopkeeper::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < PLAYERINFOMANAGER->getViewDistance())
	{
		shopkeeper->animationRender(getMemDC(), renderPos);
	}
}

bool Shopkeeper::interact(Player * player)
{
	return false;
}
