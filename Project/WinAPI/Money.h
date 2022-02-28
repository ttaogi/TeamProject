#pragma once

#include "Object.h"

class Money : public Object
{
private:
	int quantity;
public:
	HRESULT init(Scene* scenePtr, POINT position);
	void release(void);
	void update(void);
	void render(void);

	bool interact(Player* player);

	int getQuantity() const { return quantity; }
	void setQuantity(int quan);

	Money();
	virtual ~Money();
};