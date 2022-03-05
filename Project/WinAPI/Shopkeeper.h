#pragma once

#include "Object.h"

class Shopkeeper : public Object
{
private:
	Animator* shopkeeper;
	
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	Shopkeeper() {}
	virtual ~Shopkeeper() {}
};

