#include "Stdafx/stdafx.h"

#include "Timer.h"

Timer::Timer() { }

Timer::~Timer() { }

void Timer::Init() {
	// 초당 진동수를 체크. 고성능 타이머를 지원하면 true, 아니면 false를 반환.
	// periodFrequency에 초당 파알 할 수 있는 시간이 저장.
	// 밀리 세컨드까지 계산이 가능하면 1000이 저장됨.
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency)) {
		isHardware = true;

		// 특정 시점에서 몇 번 진동했는지(현재 틱)를 확인.
		QueryPerformanceCounter((LARGE_INTEGER*)&lastTime);
		timeScale = 1.0f / periodFrequency;
	}
	else {
		isHardware = false;

		lastTime = timeGetTime();
		timeScale = 0.001f;
	}

	frameRate = 0;
	FPSFrameCount = 0;
	FPSTimeElapsed = 0.0f;
	worldTime = 0.0f;
}

// 현재 시간.
void Timer::Tick(float lockFPS) {
	if (isHardware)
		QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
	else
		curTime = timeGetTime();

	timeElapsed = (curTime - lastTime) * timeScale;

	if (lockFPS > 0.0f) {
		while (timeElapsed < (1 / lockFPS)) {
			if (isHardware) {
				QueryPerformanceCounter((LARGE_INTEGER*)&curTime);
			}
			else {
				curTime = timeGetTime();
			}

			timeElapsed = (curTime - lastTime) * timeScale;
		}
	}

	lastTime = curTime;
	FPSFrameCount++;
	FPSTimeElapsed += timeElapsed;	// 초당 프레임 시간 경과량.
	worldTime += timeElapsed;		// 전체 시간 경과량.

	if (FPSTimeElapsed > 1.0f) {
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0f;
	}
}

// 현재 FPS.
unsigned long Timer::GetFrameRate(std::wstring &_str) const {
	_str = L"FPS : " + to_wstring(frameRate);
	return frameRate;
}
