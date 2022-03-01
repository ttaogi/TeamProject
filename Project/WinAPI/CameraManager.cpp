#include "Stdafx.h"

#include "CameraManager.h"

#include "Player.h"

HRESULT CameraManager::init(Player* _target)
{
	target = _target;
	coordinateRevision = POINT{ 0, 0 };
	return S_OK;
}

void CameraManager::update()
{
	if (target)
	{
		coordinateRevision = GridPointToPixelPointCenter(target->getPos());
		coordinateRevision.x -= WINSIZEX / 2;
		coordinateRevision.y -= WINSIZEY / 2;
	}
	else
		coordinateRevision = POINT{ 0, 0 };
}

void CameraManager::release() { }

POINT CameraManager::getRevision() { return coordinateRevision; }

CameraManager::CameraManager()
{
	target = NULL;
	coordinateRevision = POINT{ 0, 0 };
}

CameraManager::~CameraManager() { release(); }
