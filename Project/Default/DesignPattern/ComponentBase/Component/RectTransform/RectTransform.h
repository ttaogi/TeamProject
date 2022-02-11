#pragma once

#include "DesignPattern/ComponentBase/Component/Component.h"

class RectTransform : public Component
{
private:
	RECT rect;
protected:
public:
	RectTransform();
	virtual ~RectTransform() {}

	virtual void Operation() override;

	RECT GetRect() const { return rect; }
	void SetRect(RECT _rect) { rect = _rect; }
	RECT GetScreenRect() const;
};
