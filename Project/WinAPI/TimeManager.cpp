#include "Stdafx.h"
#include "TimeManager.h"

HRESULT TimeManager::init(void)
{
	_timer = new Timer;
	_timer->init();

	return S_OK;
}

void TimeManager::release(void)
{
	if (_timer != nullptr)
	{
		SAFE_DELETE(_timer);
		_timer = nullptr;
	}
}

void TimeManager::update(float lock)
{
	if (_timer != nullptr)
	{
		_timer->tick(lock);
	}
}

void TimeManager::render(HDC hdc)
{
	char str[256];

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));

	/*
	_DEBUG
	-Release Mode 가 아닌 Debug 일떄만 실행
	ㄴ 개발을 하면서 테스트의 용도가 강하다.
	*/

#ifdef _DEBUG
	//assert()
	if (_timer != nullptr)
	{
		//프레임 시간
		sprintf_s(str, "FramePerSec : %d", _timer->gerFrameRate());
		TextOut(hdc, 100, 100, str, (int)strlen(str));

		//월드 시간
		sprintf_s(str, "WorldTime : %f", _timer->getWorldTime());
		TextOut(hdc, 100, 120, str, (int)strlen(str));

		//갱신 시간
		sprintf_s(str, "ElapsedTime : %f", _timer->gerElapsedTime());
		TextOut(hdc, 100, 140, str, (int)strlen(str));
	}

//Release
#else
	if (_timer != nullptr)
	{
		//프레임 시간
		sprintf_s(str, "FramePerSec : %d", _timer->gerFrameRate());
		TextOut(hdc, 0, 0, str, strlen(str));
	}

#endif
}


