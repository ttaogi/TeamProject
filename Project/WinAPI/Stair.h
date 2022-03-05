#pragma once

#include "Object.h"

class Stair : public Object
{
private:
	std::string nextSceneKey;
	Image* stripe;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);
	void renderMinimap(HDC _hdc) override;

	bool interact(Player* player);
	void setNextSceneKey(std::string _nextSceneKey);

	Stair();
	virtual ~Stair();
};