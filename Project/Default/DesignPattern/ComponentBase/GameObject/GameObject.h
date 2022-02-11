#pragma once

#include <list>

#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"

class GameObject {
private:
	const Component_ID id = (const Component_ID)L"GameObject";
	Transform transform;
public:
	std::list<Component*> cList;
public:
	GameObject();
	~GameObject();

	void Operation();

	Component_ID GetComponentID();
	void		AddComponent(Component* _c);
	void		RemoveComponent(Component* _c);
	Component*	GetComponent(Component_ID _id);
	template<class T>
	T* GetComponent() {
		if (cList.size() == 0) return NULL;

		T* c = new T();

		for (auto it = cList.begin(); it != cList.end(); ++it) {
			if (!strcmp((*it)->GetComponentID(), c->GetComponentID())) {
				delete c;
				return dynamic_cast<T*>(*it);
				//return ((T*)*it);
			}
		}

		delete c;
		return NULL;
	}
};
