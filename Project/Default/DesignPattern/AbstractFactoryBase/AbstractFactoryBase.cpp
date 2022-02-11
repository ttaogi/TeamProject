#include "Stdafx/stdafx.h"

#include "AbstractFactoryBase.h"

#pragma region AbstractFactoryButton
AbstractFactoryButton::AbstractFactoryButton() { }

AbstractFactoryButton::~AbstractFactoryButton() { }

GameObject* AbstractFactoryButton::GetObject(
	BUTTON_FACTORY_TYPE _type,
	std::function<void()> _callBack_v_CB_v,
	RECT* _rect, Image* _image)
{
	GameObject* go = NULL;

	switch (_type) {
	case BUTTON_FACTORY_TYPE::DEFAULT:
		go = ButtonFactory::GetSingleton()
			->GetObject(_callBack_v_CB_v, _rect, _image);
		break;
	}

	return go;
}
#pragma endregion AbstractFactoryButton
