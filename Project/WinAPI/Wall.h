#pragma once

#include "Object.h"

class Wall : public Object
{
private:
	int hp;
public:
	HRESULT init(OBJECT_TYPE _type, POINT _pos);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	Wall();
	~Wall();
};