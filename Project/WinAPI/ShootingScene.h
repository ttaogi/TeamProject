#pragma once
#include "GameNode.h"
#include "Rocket.h"
#include "EnemyManager.h"
#include "ShootingEffect.h"

class ShootingScene:public GameNode
{
private:
	Rocket* _rocket;
	EnemyManager* _em;
	MissileEffect* _missileEffect;
	BeamEffect* _beamEffect;

	float _x, _y;
	char _text[64];

public:
	HRESULT init(void);
	void release(void);
	void update(void);
	void render(void);

	virtual void collision(void);

	ShootingScene() {}
	~ShootingScene() {}
};

