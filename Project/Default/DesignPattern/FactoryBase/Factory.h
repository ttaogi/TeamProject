#pragma once

#include <functional>

#include "DesignPattern/SingletonBase/SingletonBase.h"

class GameObject;
class Image;

#pragma region ButtonFactory
class ButtonFactory : public SingletonBase<ButtonFactory>
{
private:
protected:
public:
	ButtonFactory();
	~ButtonFactory();

	GameObject* GetObject(std::function<void()> _callBack_v_CB_v,
		RECT* _rect, Image* _image, std::wstring _str = L"");
};
#pragma endregion ButtonFactory
