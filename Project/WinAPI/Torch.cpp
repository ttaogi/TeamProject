#include "stdafx.h"

#include "Torch.h"

#include "Animation.h"
#include "Animator.h"
#include "Player.h"

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
	POINT p = GridPointToPixelPointLeftTop(pos);
	_info.stripe->render(getMemDC(), (int)p.x, (int)p.y);
}

bool Torch::interact(Player * player)
{
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
