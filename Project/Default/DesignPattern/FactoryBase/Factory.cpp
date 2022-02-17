#include "Stdafx/stdafx.h"

#include "Factory.h"

#include "DesignPattern/ComponentBase/GameObject/GameObject.h"
#include "DesignPattern/ComponentBase/Component/Button/Button.h"
#include "DesignPattern/ComponentBase/Component/RectTransform/RectTransform.h"
#include "DesignPattern/ComponentBase/Component/Rendered/RenderedImage/RenderedImage.h"
#include "DesignPattern/ComponentBase/Component/Transform/Transform.h"

#pragma region ButtonFactory
ButtonFactory::ButtonFactory() { }

ButtonFactory::~ButtonFactory() { }

GameObject* ButtonFactory::GetObject(
	std::function<void()> _callBack_v_CB_v,
	RECT* _rect, Image* _image, std::wstring _str)
{
	GameObject* go = new GameObject();
	Button* btn = new Button(_str);
	RectTransform* rcT = new RectTransform();
	RenderedImage* rImg = new RenderedImage();

	btn->SetCallBack_v_CB_v(_callBack_v_CB_v);
	btn->Init();
	rcT->SetRect(RECT{ 0, 0, 200, 150 });
	rImg->SetImage(_image);

	go->AddComponent(btn);
	go->AddComponent(rcT);
	go->AddComponent(rImg);

	return go;
}
#pragma endregion ButtonFactory
