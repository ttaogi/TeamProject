#include "stdafx.h"

#include "Torch.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"
#include "Scene.h"


HRESULT Torch::init(Scene * scenePtr, POINT position)
{
	// GameNode
	pos = position;
	// Object.
	destroyed = false;
	type = OBJECT_TYPE::EUIP_TORCH;
	animator = NULL;
	scene = scenePtr;
	_info = ITEMINFOMANAGER->getItemInfo(ITEM_DETAIL::TORCH);

	return S_OK;
}

void Torch::release(void)
{
}

void Torch::update(void)
{
}

void Torch::render(void)
{
	POINT renderPos = GridPointToPixelPointLeftTop(pos);
	POINT revision = CAMERAMANAGER->getRevision();

	renderPos.x -= revision.x;
	renderPos.y -= revision.y;

	POINT p = scene->getPlayer()->getPos();
	int distance = abs(p.x - pos.x) + abs(p.y - pos.y);

	if (distance < 8)
	{
		_info.stripe->render(getMemDC(), (int)renderPos.x, (int)renderPos.y);
	}
}

bool Torch::interact(Player * player)
{
	if (player == NULL)
	{
		destroyed = true;
		return true;
	}

	if (PLAYERINFOMANAGER->getMoney() >= _info.price)
	{
		PLAYERINFOMANAGER->setTorch(_info);
		PLAYERINFOMANAGER->setMoney(PLAYERINFOMANAGER->getMoney() - _info.price);
		destroyed = true;
		return true;
	}

	else
	{
		return false;
	}
}
