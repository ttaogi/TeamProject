#pragma once

#include "Object.h"

class Dagger : public Object
{
private:
	Item _info;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	Dagger() {}
	virtual ~Dagger() {}
};

class BroadSword : public Object
{
private:
	Item _info;

public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	BroadSword() {}
	virtual ~BroadSword() {}
};

