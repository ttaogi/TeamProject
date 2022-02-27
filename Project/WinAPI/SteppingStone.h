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
	~SteppingStoneTop();
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
	~SteppingStoneRight();
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
	~SteppingStoneBottom();
};
