#include "Stdafx/stdafx.h"

#include "RectTransform.h"
#include "DesignPattern/ComponentBase/GameObject/GameObject.h"

RectTransform::RectTransform()
	: Component((const Component_ID)typeid(RectTransform).name()) { }

void RectTransform::Operation() { }

RECT RectTransform::GetScreenRect() const {
	Transform* t = NULL;

	if (gameObject == NULL) return RECT{ 0, 0, 0, 0 };
	t = gameObject->GetComponent<Transform>();
	if (t == NULL) return RECT{ 0, 0, 0, 0 };
	POINT pos = t->GetPosition().ToPoint();

	return RECT{rect.left + pos.x, rect.top + pos.y, rect.right + pos.x, rect.bottom + pos.y};
}
