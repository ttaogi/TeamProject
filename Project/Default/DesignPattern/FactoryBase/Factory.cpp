#include "Stdafx/stdafx.h"

#include "Factory.h"

#pragma region ButtonFactory
ButtonFactory::ButtonFactory() { }

ButtonFactory::~ButtonFactory() { }

GameObject* ButtonFactory::GetObject(
	std::function<void()> _callBack_v_CB_v,
	RECT* _rect, Image* _image)
{
	GameObject* go = new GameObject();
	Button* btn = new Button();
	RectTransform* rcT = new RectTransform();
	RenderedImage* rImg = new RenderedImage();

	btn->SetCallBack_v_CB_v(_callBack_v_CB_v);
	btn->Init();
	rcT->SetRect(RECT{ 0, 0, 200, 150 });
	rImg->SetImage(IMG->FindImage(KEY_UI_START_BUTTON_STRIPE));

	go->AddComponent(btn);
	go->AddComponent(rcT);
	go->AddComponent(rImg);

	return go;
}
#pragma endregion ButtonFactory
