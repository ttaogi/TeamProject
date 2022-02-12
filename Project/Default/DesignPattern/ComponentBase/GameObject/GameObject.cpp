#include "Stdafx/stdafx.h"

#include "GameObject.h"

GameObject::GameObject()
{
	AddComponent(&transform);
	tag = L"";
	active = true;
}

GameObject::~GameObject()
{
	for (auto iter = cList.begin(); iter != cList.end(); ++iter)
		SAFE_DELETE(*iter);
}

void GameObject::Operation()
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		(*it)->Operation();
}

void GameObject::AddComponent(Component* _c)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (!strcmp((*it)->GetComponentID(), _c->GetComponentID())) return;

	_c->gameObject = this;
	_c->transform = &transform;
	cList.push_back(_c);
}

void GameObject::RemoveComponent(Component* _c)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (!strcmp((*it)->GetComponentID(), _c->GetComponentID())) cList.erase(it);
}

Component* GameObject::GetComponent(Component_ID _id)
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		if (!strcmp((*it)->GetComponentID(), _id)) return *it;
	return NULL;
}

Component_ID GameObject::GetComponentID() { return id; }
