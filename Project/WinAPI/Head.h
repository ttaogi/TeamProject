#pragma once

#include "Object.h"

class Head : public Object
{
private:
	Item _info;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);
	   
	Head() {}
	virtual ~Head() {}
};

