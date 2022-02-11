#include "Stdafx/stdafx.h"

#include "Behaviour.h"

Behaviour::Behaviour()
	: Component((const Component_ID)typeid(Behaviour).name())
{
	enabled = true;
}

Behaviour::~Behaviour() { }

void Behaviour::Operation() { }
