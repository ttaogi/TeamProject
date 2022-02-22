#include "Stdafx/stdafx.h"

#include "GameObject.h"

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"

GameObject::GameObject()
{
	AddComponent(&transform);
	tag = L"";
	active = true;
}

GameObject::~GameObject()
{
	for (auto it = goList.begin(); it != goList.end();)
	{
		SAFE_DELETE(*it);
		it = goList.erase(it);
	}
	for (auto it = cList.begin(); it != cList.end(); ++it)
		SAFE_DELETE(*it);
}

void GameObject::Operation()
{
	for (auto it = cList.begin(); it != cList.end(); ++it)
		(*it)->Operation();
}

void GameObject::Update()
{
	if (active)
	{
		for (auto it = cList.begin(); it != cList.end(); ++it)
		{
			MonoBehaviour* mb = IsDerivedFromMonoBehaviour(*it);
			if (mb) mb->Update();
		}
		for (auto it = goList.begin(); it != goList.end(); ++it)
			(*it)->Update();
	}
}

void GameObject::Render(HDC _hdc)
{
	if (active)
	{
		for (auto it = cList.begin(); it != cList.end(); ++it)
		{
			RenderedAnimator* rAnim = IsDerivedFromRenderedAnimator(*it);
			if (rAnim) rAnim->Render(_hdc);
		}

		for (auto it = goList.begin(); it != goList.end(); ++it)
			(*it)->Render(_hdc);
	}
}

void GameObject::RenderUI(HDC _hdc)
{
	if (active)
	{
		RenderedImage* rImg = GetComponent<RenderedImage>();
		if (rImg) rImg->Render(_hdc);

		for (auto it = goList.begin(); it != goList.end(); ++it)
			(*it)->RenderUI(_hdc);
	}
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

bool GameObject::AddGameObject(GameObject* _go)
{
	if (!_go) return true;

	for (auto it = goList.begin(); it != goList.end(); ++it)
		if ((*it)->GetTag() == _go->GetTag().c_str()) return false;

	_go->SetParent(this);
	goList.push_back(_go);

	return true;
}

void GameObject::RemoveGameObject(GameObject* _go)
{
	if (!_go) return;

	for(auto it = goList.begin(); it != goList.end(); ++it)
		if ((*it) == _go)
		{
			goList.erase(it);
			break;
		}
}

void GameObject::RemoveGameObject(std::wstring _tag)
{
	for(auto it = goList.begin(); it != goList.end(); ++it)
		if ((*it)->GetTag() == _tag)
		{
			goList.erase(it);
			break;
		}
}

GameObject* GameObject::GetGameObject(std::wstring _tag)
{
	for (auto it = goList.begin(); it != goList.end(); ++it)
		if ((*it)->GetTag() == _tag) return *it;
	return NULL;
}

GameObject * GameObject::GetParent() { return parent; }

void GameObject::SetParent(GameObject* _go) { parent = _go; }

Component_ID GameObject::GetComponentID() { return id; }
