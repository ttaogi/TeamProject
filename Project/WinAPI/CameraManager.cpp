#include "Stdafx.h"

#include "CameraManager.h"

#include "Player.h"

HRESULT CameraManager::init(Player* _target)
{
	target = _target;
	if (target)
	{
		coordinateRevision = GridPointToPixelPointCenter(target->getPos());
		coordinateRevision.x -= WINSIZEX / 2;
		coordinateRevision.y -= WINSIZEY / 2;
		previousPosX = coordinateRevision.x;
		previousPosY = coordinateRevision.y;
	}
	else
	{
		coordinateRevision = POINT{ 0, 0 };
		previousPosX = coordinateRevision.x;
		previousPosY = coordinateRevision.y;
	}

	return S_OK;
}

void CameraManager::update()
{
	if (target)
	{
		coordinateRevision = GridPointToPixelPointCenter(target->getPos());
		coordinateRevision.x -= WINSIZEX / 2;
		coordinateRevision.y -= WINSIZEY / 2;

		previousPosX = (0.8f * previousPosX + 0.2f * coordinateRevision.x);
		previousPosY = (0.8f * previousPosY + 0.2f * coordinateRevision.y);
		coordinateRevision.x = (int)previousPosX;
		coordinateRevision.y = (int)previousPosY;
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
	previousPosX = previousPosY = 0.0f;
}

CameraManager::~CameraManager() { release(); }
