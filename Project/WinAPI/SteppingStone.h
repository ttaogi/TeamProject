#pragma once

#include "Object.h"

class SteppingStoneLeft : public Object
{
private:
	Image* stripe;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	SteppingStoneLeft();
	~SteppingStoneLeft();
};