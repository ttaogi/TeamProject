#include "Stdafx/stdafx.h"

#include "Transform.h"

Transform::Transform()
	: Component((const Component_ID)typeid(Transform).name())
{
	position = F_POINT{ 0, 0 };
}

Transform::Transform(Transform* _t) : Component((const Component_ID)L"Transform")
{
	gameObject = _t->gameObject;
	transform = _t->transform;
	position = _t->GetPosition();
}

Transform::~Transform() { }

void Transform::Operation() { }
