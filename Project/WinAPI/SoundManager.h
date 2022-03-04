#pragma once

#include "SingletonBase.h"
#pragma warning(push)
#pragma warning(disable: 26812)
#include "fmod.hpp"
#pragma warning(pop)

using namespace FMOD;

#define EXTRACHANNELBUFFER	5
#define SOUNDBUFFER			20
#define TOTALSOUNDBUFFER	(SOUNDBUFFER + EXTRACHANNELBUFFER)

class SoundManager : public SingletonBase<SoundManager> {
private:
	std::map<std::string, Sound**> m_totalSounds;

	System* m_system;
	Sound** m_sound;
	Channel** m_channel;

	Sound* shopKepperSound;
	Channel* shopKeeperChannel;
	
	FMOD_RESULT result;
	FMOD::System* mSystem;

public:
	SoundManager();
	~SoundManager();

	HRESULT init();
	void release();
	void update();

	// bgm - true : bgm, false : sfx.
	void addSound(std::string _keyName, std::string _fileName, bool _bgm = FALSE, bool _loop = FALSE);
	void addSound3d(std::string _fileName);
	// volume : 0.0f ~ 1.0f.
	void play(std::string _keyName, float _volume = 1.0f);
	// go to start point.
	void stop(std::string _keyName);
	void allStop();
	void pause(std::string _keyName);
	void resume(std::string _keyName);
	
	void setSound3DInfo(float px, float py, float pz);
	void updateListener(POINT _pos);
	Channel* play3DSound(float volume, float x, float y, float z);
	void stop3DSound();

	bool isPlaySound(std::string _keyName);
	bool isPauseSound(std::string _keyName);
};
