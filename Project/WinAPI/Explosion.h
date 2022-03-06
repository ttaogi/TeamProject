#pragma once

#include "Object.h"


class Explosion : public Object
{
private:
	Item _info;
	CHARACTER_STATE state;
	Animator* bombAnimator;
	Animator* explosionAnimator;
	bool sound;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);
	
	bool interact(Player* player) { return true; }

	Explosion() {}
	~Explosion() {}
};

