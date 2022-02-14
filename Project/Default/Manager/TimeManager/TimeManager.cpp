#include "Stdafx/stdafx.h"

#include "TimeManager.h"

TimeManager::TimeManager() {
	timer = new Timer();
	timer->Init();
}

TimeManager::~TimeManager() {
	SAFE_DELETE(timer);
}

void TimeManager::Init() {
}

void TimeManager::Release() {
}

void TimeManager::Update(float _lock) {
	if (timer) {
		timer->Tick(_lock);
	}
}

void TimeManager::Render(HDC _hdc) {
	std::wstring str;

	SetBkMode(_hdc, TRANSPARENT);
	SetTextColor(_hdc, RGB(255, 255, 255));

#ifdef _DEBUG
	if (timer) {
		timer->GetFrameRate(str);
		TextOut(_hdc, 0, 0, str.c_str(), (int)str.length());
		str = to_wstring(timer->GetElapsedTime());
		TextOut(_hdc, 0, 20, str.c_str(), (int)str.length());
		str = to_wstring(timer->GetWorldTime());
		TextOut(_hdc, 0, 40, str.c_str(), (int)str.length());
	}
#else
	if (timer) {
		//
	}
#endif
	SetTextColor(_hdc, RGB(0, 0, 0));
	SetBkMode(_hdc, OPAQUE);
}
