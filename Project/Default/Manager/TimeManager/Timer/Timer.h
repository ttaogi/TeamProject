#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

/*
Timer
윈도우가 시작된 이후 지난 시간을 반환
해상도와 클럭
	-해상도 : 다양한 시간 함수들은 시간을 측정하기 위한 저마다의 Tick 계산ㄹ로직이 있다.
		1분을 기준으로 얼마나 많은 프레임으로 나눌 수 있는지를 뜻한다.
		1분 동안 얼마나 많은 Tick으로 나눠서 시간의 정확도를 높이느냐에 따라서
		고해상도와 저해상도로 나뉜다.
	-클럭 : 타이머에서 애기하는 클럭은 CPU 클럭을 의미한다.
		클럭은 디지털 회로의 전기적 진동수이며 Hz로 표기한다.
고성능 타이머의 경우 성능을 향상시키기 위해 중첩이 필요하다.
	약 900만 분의 1초까지 측정.
기본값으로 셋팅하고 사용 시 백만 분의 1초까지 측정.
*/

class Timer {
private:
	float timeScale;				// 경과시간 조절.
	float timeElapsed;				// 마지막 시간과 현재시간의 경과값.
	bool isHardware;				// 고성능 타이머 지원 여부.

	__int64 curTime;				// 현재 시간.
	__int64 lastTime;				// 이전 시간.
	__int64 periodFrequency;		// 시간 주기.

	unsigned long frameRate;
	unsigned long FPSFrameCount;
	float FPSTimeElapsed;
	float worldTime;				// 전체 경과 시간.
public:
	Timer();
	~Timer();

	void Init();

	void Tick(float lockFPS = 0.0f);
	unsigned long GetFrameRate(std::wstring &_str) const;
	inline float GetElapsedTime() const { return timeElapsed; }
	inline float GetWorldTime() const { return worldTime; }
};