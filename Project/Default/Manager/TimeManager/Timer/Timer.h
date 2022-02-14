#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

/*
Timer
�����찡 ���۵� ���� ���� �ð��� ��ȯ
�ػ󵵿� Ŭ��
	-�ػ� : �پ��� �ð� �Լ����� �ð��� �����ϱ� ���� �������� Tick ��ꤩ������ �ִ�.
		1���� �������� �󸶳� ���� ���������� ���� �� �ִ����� ���Ѵ�.
		1�� ���� �󸶳� ���� Tick���� ������ �ð��� ��Ȯ���� ���̴��Ŀ� ����
		���ػ󵵿� ���ػ󵵷� ������.
	-Ŭ�� : Ÿ�̸ӿ��� �ֱ��ϴ� Ŭ���� CPU Ŭ���� �ǹ��Ѵ�.
		Ŭ���� ������ ȸ���� ������ �������̸� Hz�� ǥ���Ѵ�.
���� Ÿ�̸��� ��� ������ ����Ű�� ���� ��ø�� �ʿ��ϴ�.
	�� 900�� ���� 1�ʱ��� ����.
�⺻������ �����ϰ� ��� �� �鸸 ���� 1�ʱ��� ����.
*/

class Timer {
private:
	float timeScale;				// ����ð� ����.
	float timeElapsed;				// ������ �ð��� ����ð��� �����.
	bool isHardware;				// ���� Ÿ�̸� ���� ����.

	__int64 curTime;				// ���� �ð�.
	__int64 lastTime;				// ���� �ð�.
	__int64 periodFrequency;		// �ð� �ֱ�.

	unsigned long frameRate;
	unsigned long FPSFrameCount;
	float FPSTimeElapsed;
	float worldTime;				// ��ü ��� �ð�.
public:
	Timer();
	~Timer();

	void Init();

	void Tick(float lockFPS = 0.0f);
	unsigned long GetFrameRate(std::wstring &_str) const;
	inline float GetElapsedTime() const { return timeElapsed; }
	inline float GetWorldTime() const { return worldTime; }
};