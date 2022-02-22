#pragma once
#include "SingletonBase.h"

//������ ���� ��� ���̺귯��
//PlaySound()�� ����ϱ� ����
//mciSendString()�� ����ϱ� ����
//mci: Media Control Interface (��ġ������)

class TempSoundManager : public SingletonBase <TempSoundManager>
{
public:
	HRESULT init();
	void addMp3FileWithKey(string key, string fileName);
	void addWaveileWithKey(string key, string fileName);
	void playEffectSoundWave(char* fileName);
	void playSoundWithKey(string key);
	void stopMp3WithKey(string key);


	TempSoundManager() {}
	~TempSoundManager() {}
};

