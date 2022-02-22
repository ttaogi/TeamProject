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
public:
	SoundManager();
	~SoundManager();

	HRESULT init();
	void release();
	void update();

	// bgm - true : bgm, false : sfx.
	void addSound(std::string _keyName, std::string _fileName, bool _bgm = FALSE, bool _loop = FALSE);
	// volume : 0.0f ~ 1.0f.
	void play(std::string _keyName, float _volume = 1.0f);
	// go to start point.
	void stop(std::string _keyName);
	void allStop();
	void pause(std::string _keyName);
	void resume(std::string _keyName);

	bool isPlaySound(std::string _keyName);
	bool isPauseSound(std::string _keyName);
};
