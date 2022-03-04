#include "Stdafx.h"

#include "SoundManager.h"

SoundManager::SoundManager()
	: m_system(NULL), m_channel(NULL), m_sound(NULL),
	shopKepperSound(NULL), shopKeeperChannel(NULL) { }

SoundManager::~SoundManager() { }

HRESULT SoundManager::init()
{
	System_Create(&m_system);

	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	m_sound = new Sound*[TOTALSOUNDBUFFER];
	m_channel = new Channel*[TOTALSOUNDBUFFER];

	shopKepperSound = NULL;
	shopKeeperChannel = NULL;

	for (int i = 0; i < TOTALSOUNDBUFFER; i++)
	{
		m_sound[i] = NULL;
		m_channel[i] = NULL;
	}

	return S_OK;
}

void SoundManager::release()
{
	allStop();

	if (m_channel != NULL || m_sound != NULL)
	{
		for (int i = 0; i < TOTALSOUNDBUFFER; i++)
		{
			if (m_channel != NULL && m_channel[i] != NULL) m_channel[i]->stop();
			if (m_sound != NULL && m_sound[i] != NULL) m_sound[i]->release();
		}
	}
	SAFE_DELETE_ARRAY(m_sound);
	SAFE_DELETE_ARRAY(m_channel);

	if (shopKeeperChannel) shopKeeperChannel->stop();
	if (shopKepperSound) shopKepperSound->release();

	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}
}

void SoundManager::update()
{
	m_system->update();
}

void SoundManager::addSound(string _keyName, string _wfileName, bool _bgm, bool _loop)
{
	if (_loop) {
		if (_bgm) {
			m_system->createStream(_wfileName.c_str(),
				FMOD_LOOP_NORMAL, NULL,
				&m_sound[m_totalSounds.size()]);
		}
		else {
			m_system->createSound(_wfileName.c_str(),
				FMOD_LOOP_NORMAL, NULL,
				&m_sound[m_totalSounds.size()]);
		}
	}
	else {
		m_system->createSound(_wfileName.c_str(),
			FMOD_DEFAULT, NULL,
			&m_sound[m_totalSounds.size()]);
	}
	m_totalSounds[_keyName] = &m_sound[m_totalSounds.size()];
}

void SoundManager::play(string _keyName, float _volume) {
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_system->playSound(*(iter->second), NULL, false, &m_channel[count]);
			m_channel[count]->setVolume(_volume);
			break;
		}
	}
}

void SoundManager::stop(string _keyName) {
	int count = 0;
	map<string, Sound**>::iterator iter;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_channel[count]->stop();
			break;
		}
	}
}

void SoundManager::allStop() {
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, ++count) {
		m_channel[count]->stop();
	}
	stop3DSound();
}

void SoundManager::pause(string _keyName) {
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_channel[count]->setPaused(true);
			break;
		}
	}
}

void SoundManager::resume(string _keyName) {
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_channel[count]->setPaused(false);
			break;
		}
	}
}

void SoundManager::setSound3DInfo(float px, float py, float pz)
{
	FMOD_VECTOR pos = { px, py, pz };
	FMOD_VECTOR vel = { 0, 0, 0 };

	if(shopKeeperChannel)
		shopKeeperChannel->set3DAttributes(&pos, &vel);
}

void SoundManager::updateListener(POINT _pos)
{
	FMOD_VECTOR pos = { (float)_pos.x, (float)_pos.y, 0};
	FMOD_VECTOR vel = { 0, 0, 0 };
	FMOD_VECTOR forward = { 0, -1, 0 };
	FMOD_VECTOR up = { 0, 0, 1};

	m_system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);
}

void SoundManager::addSound3d(std::string _fileName)
{
	m_system->createSound(_fileName.c_str(), FMOD_SOFTWARE | FMOD_3D, NULL, &shopKepperSound);

	shopKepperSound->set3DMinMaxDistance(2, 2000);
	shopKepperSound->setMode(FMOD_LOOP_NORMAL);
}

Channel* SoundManager::play3DSound(float volume, float x, float y, float z)
{
	FMOD_VECTOR pos = { x, y, z }; // z??
	FMOD_VECTOR vel = { 0, 0, 0 };
	shopKeeperChannel->setVolume(volume);
	shopKeeperChannel->set3DAttributes(&pos, &vel);

	m_system->playSound(shopKepperSound, NULL, false, &shopKeeperChannel);

	return shopKeeperChannel;
}

void SoundManager::stop3DSound() { shopKeeperChannel->stop(); }

bool SoundManager::isPlaySound(string _keyName) {
	bool isPlay = false;
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_channel[count]->isPlaying(&isPlay);
			break;
		}
	}

	return isPlay;
}

bool SoundManager::isPauseSound(string _keyName) {
	bool isPaused = false;
	int count = 0;
	for (auto iter = m_totalSounds.begin(); iter != m_totalSounds.end(); ++iter, count++) {
		if (_keyName == iter->first) {
			m_channel[count]->getPaused(&isPaused);
			break;
		}
	}

	return isPaused;
}