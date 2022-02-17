#pragma once

#include <windef.h>

#include "DesignPattern/ComponentBase/Component/Behaviour/Behaviour.h"

class Rendered : public Behaviour
{
private:
protected:
public:
	Rendered();
	virtual ~Rendered();

	virtual void Operation() override;

	virtual void Render(HDC _hdc) = 0;
};