#pragma once

#include "Object.h"

class Wall : public Object
{
private:
public:
	HRESULT init(OBJECT_TYPE _type, POINT _pos);
	void release(void);
	void update(void);
	void render(void);

	Wall();
	~Wall();
};