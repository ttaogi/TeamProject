#pragma once

#include "Object.h"

class Heal : public Object
{
private:
	Item _info;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	Heal() {}
	virtual ~Heal() {}
};

