#include "Stdafx/stdafx.h"

#include "Timer.h"

Timer::Timer() { }

Timer::~Timer() { }

void Timer::Init() {
	// �ʴ� �������� üũ. ���� Ÿ�̸Ӹ� �����ϸ� true, �ƴϸ� false�� ��ȯ.
	// periodFrequency�� �ʴ� �ľ� �� �� �ִ� �ð��� ����.
	// �и� ��������� ����� �����ϸ� 1000�� �����.
	if (QueryPerformanceFrequency((LARGE_INTEGER*)&periodFrequency)) {
		isHardware = true;

		// Ư�� �������� �� �� �����ߴ���(���� ƽ)�� Ȯ��.
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

// ���� �ð�.
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
	FPSTimeElapsed += timeElapsed;	// �ʴ� ������ �ð� �����.
	worldTime += timeElapsed;		// ��ü �ð� �����.

	if (FPSTimeElapsed > 1.0f) {
		frameRate = FPSFrameCount;
		FPSFrameCount = 0;
		FPSTimeElapsed = 0.0f;
	}
}

// ���� FPS.
unsigned long Timer::GetFrameRate(std::wstring &_str) const {
	_str = L"FPS : " + to_wstring(frameRate);
	return frameRate;
}
