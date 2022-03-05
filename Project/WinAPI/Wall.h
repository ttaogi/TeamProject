#pragma once

#include "Object.h"

class Wall : public Object
{
private:
	int hp;

	HRESULT init(Scene* scenePtr, POINT position) { return S_OK; }
public:
	HRESULT init(OBJECT_TYPE _type, POINT _pos, Scene* _scenPtr);
	void release(void);
	void update(void);
	void render(void);
	void renderMinimap(HDC _hdc) override;

	bool interact(Player* player);

	Wall();
	virtual ~Wall();
};