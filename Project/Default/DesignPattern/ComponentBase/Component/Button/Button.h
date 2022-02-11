#pragma once

#include <functional>

#include "DesignPattern/ComponentBase/Component/Behaviour/MonoBehaviour/MonoBehaviour.h"

class Button : public MonoBehaviour {
private:
	std::function<void()> callBack_v_CB_v;
	std::wstring str;
public:
	Button();
	virtual ~Button();

	virtual void Operation() override;

	void Init();
	void Update(HWND _hWnd);
	void LateUpdate();

	void SetCallBack_v_CB_v(std::function<void()> _callBack);
	std::wstring	GetString() const { return str; }
	void			SetString(std::wstring _str) { str = _str; }
};