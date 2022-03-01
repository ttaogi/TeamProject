#pragma once

#include "SingletonBase.h"

class Player;

class CameraManager : public SingletonBase<CameraManager>
{
private:
	Player* target;
	POINT coordinateRevision;
public:
	HRESULT init(Player* _target = NULL);
	void update();
	void release();

	POINT getRevision();

	CameraManager();
	~CameraManager();
};