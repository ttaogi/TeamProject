#pragma once

#include <windef.h>

#include "DesignPattern/ComponentBase/Component/Component.h"
#include "Utility/CommonClasses/CommonClasses.h"

class Transform : public Component {
private:
	friend class GameObject;
	F_POINT position;
protected:
public:
	Transform();
	Transform(Transform* _t);
	virtual ~Transform();

	virtual void Operation() override;

	F_POINT	GetPosition() const { return position; }
	void	SetPosition(const F_POINT _position) { position = _position; }
};