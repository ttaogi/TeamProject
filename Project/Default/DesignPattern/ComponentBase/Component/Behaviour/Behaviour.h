#pragma once

#include "DesignPattern/ComponentBase/Component/Component.h"

class Behaviour : virtual public Component
{
private:
protected:
public:
	bool enabled;
public:
	Behaviour();
	virtual ~Behaviour();

	virtual void Operation() override;

	bool GetEnabled() const { return enabled; }
	void SetEnabled(bool _enabled) { enabled = _enabled; }
};