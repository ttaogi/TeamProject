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
	virtual ~SteppingStoneLeft();
};

class SteppingStoneTop : public Object
{
private:
	Image* stripe;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	SteppingStoneTop();
	virtual ~SteppingStoneTop();
};

class SteppingStoneRight : public Object
{
private:
	Image* stripe;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	SteppingStoneRight();
	virtual ~SteppingStoneRight();
};

class SteppingStoneBottom : public Object
{
private:
	Image* stripe;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	SteppingStoneBottom();
	virtual ~SteppingStoneBottom();
};
