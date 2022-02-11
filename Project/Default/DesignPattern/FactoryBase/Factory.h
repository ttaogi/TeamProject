#pragma once

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"
#include "DesignPattern/SingletonBase/SingletonBase.h"

#pragma region ButtonFactory
class ButtonFactory : public SingletonBase<ButtonFactory>
{
private:
protected:
public:
	ButtonFactory();
	~ButtonFactory();

	GameObject* GetObject(std::function<void()> _callBack_v_CB_v,
		RECT* _rect, Image* _image);
};
#pragma endregion ButtonFactory
