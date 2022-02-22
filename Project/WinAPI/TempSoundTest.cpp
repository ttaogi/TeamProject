#include "Stdafx.h"
#include "TempSoundTest.h"

HRESULT TempSoundTest::init(void)
{
	TEMPSOUNDMANAGER->addMp3FileWithKey("����", "Resources/Sounds/Final.mp3");
	//TEMPSOUNDMANAGER->addMp3FileWithKey("��ü��", "Resources/Sounds/Main.mp3");

	return S_OK;
}

void TempSoundTest::update(void)
{
	if (KEYMANAGER->isOnceKeyDown('P'))
	{
		TEMPSOUNDMANAGER->playSoundWithKey("����");
		//TEMPSOUNDMANAGER->playSoundWithKey("��ü��");
	}

	if (KEYMANAGER->isOnceKeyDown('O'))
	{
		TEMPSOUNDMANAGER->playEffectSoundWave("Resources/Sounds/test.wav");
	}
}
