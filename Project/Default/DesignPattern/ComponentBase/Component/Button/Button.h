#pragma once

#include <functional>

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class Button : public MonoBehaviour
{
private:
	std::function<void()> callBack_v_CB_v;
	std::wstring str;
public:
	Button(std::wstring _str = L"");
	virtual ~Button();

	virtual void Operation() override;

	void Init() override;
	void Update() override;
	void LateUpdate() override;

	void SetCallBack_v_CB_v(std::function<void()> _callBack);
	std::wstring	GetString() const { return str; }
	void			SetString(std::wstring _str) { str = _str; }
};