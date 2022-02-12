#pragma once

#include "DesignPattern/FactoryBase/Factory.h"
#include "Utility/Enums.h"

#pragma region AbstractFactoryButton
class AbstractFactoryButton : public SingletonBase<AbstractFactoryButton>
{
private:
protected:
public:
	AbstractFactoryButton();
	~AbstractFactoryButton();

	GameObject* GetObject(BUTTON_FACTORY_TYPE _type,
		std::function<void()> _callBack_v_CB_v,
		RECT* _rect, Image* _image, std::wstring _str = L"");
};
#pragma endregion AbstractFactoryButton
