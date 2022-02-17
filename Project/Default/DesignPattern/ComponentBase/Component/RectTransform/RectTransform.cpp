#include "Stdafx/stdafx.h"

#include "RectTransform.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

RectTransform::RectTransform()
	: Component((const Component_ID)typeid(RectTransform).name()) { }

void RectTransform::Operation() { }

RECT RectTransform::GetScreenRect() const {
	Transform* t = NULL;

	if (gameObject == NULL)
		return RECT{ 0, 0, 0, 0 };

	t = gameObject->GetComponent<Transform>();
	if (t == NULL)
		return RECT{ 0, 0, 0, 0 };

	POINT pos = t->GetPosition().ToPoint();
	long width = rect.right - rect.left;
	long height = rect.bottom - rect.top;

	return RECT{pos.x - width / 2, pos.y - height / 2, 
		pos.x + width / 2, pos.y + height / 2};
}
