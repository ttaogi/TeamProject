#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"
#include "Manager/TimeManager/Timer/Timer.h"

class TimeManager : public SingletonBase<TimeManager> {
private:
	Timer* timer;
public:
	TimeManager();
	~TimeManager();

	void Init();
	void Release();
	void Update(float l_ock = 0.0f);
	void Render(HDC _hdc);

	inline float GetWorldTime() const { return timer->GetWorldTime(); }
	inline float GetElapsedTime() const { return timer->GetElapsedTime(); }
};
