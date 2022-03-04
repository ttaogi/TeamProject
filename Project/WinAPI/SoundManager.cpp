#include "Stdafx.h"

#include "SoundManager.h"

SoundManager::SoundManager() : m_system(NULL), m_channel(NULL), m_sound(NULL) { }

SoundManager::~SoundManager() { }

HRESULT SoundManager::init()
{
	System_Create(&m_system);

	m_system->init(TOTALSOUNDBUFFER, FMOD_INIT_NORMAL, 0);

	m_sound = new Sound*[TOTALSOUNDBUFFER];
	m_channel = new Channel*[TOTALSOUNDBUFFER];

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

	if (m_system != NULL)
	{
		m_system->release();
		m_system->close();
	}
}

void SoundManager::update()
{
	m_system->update();
	//if (mSilent) return;
	
	if (fading && song)
	{
		musicFadeTimeCounter -= TIMEMANAGER->getElapsedTime();
		if (musicFadeTimeCounter < 0)
		{
			if (nextSong != "")
				playSong(nextSong, 1, 0);
			nextSong = "";
			fading = false;
			musicFadeTimeCounter = 0.0;
			musicFadeTime = 0.0;
		}
		else
		{
			songChannel->setVolume(mMusicVolume * musicFadeTimeCounter / musicFadeTime);
		}
	}

	//if we have a play list...well, use it
	if (mUsePlayList && mPlayList.size())
	{
		unsigned int trackTime = 0;
		if (songChannel)
		{
			bool playing;
			songChannel->isPlaying(&playing);
			if (!playing) mTrackTime = 99999;
			else
			{
				songChannel->getPosition(&trackTime, FMOD_TIMEUNIT_MS);
				//if tracktime is zero and the last tracktime is also zero
			//	if(mTrackTime == 0 && trackTime == 0)
			//		mTrackTime = 9999;
			//	else
				mTrackTime = 0.001 * trackTime;
			}
		}
		else
			mTrackTime = 99999;			//if the song stops, move on
	//	printf("%f/%f\n", mTrackTime, mPlayList[mTrack].trackTime);
		if (mTrackTime > mPlayList[mTrack].trackTime)
			skipSong();

	}
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

void SoundManager::setSound3DInfo(SkySound soundChannel, float px, float py, float pz, float vx, float vy, float vz)
{
	if (mSilent) return;
	if (!soundChannel) return;
	if (mInitFailed) return;

	FMOD_VECTOR pos = { px, py, pz };
	FMOD_VECTOR vel = { vx, vy, vz };

	soundChannel->set3DAttributes(&pos, &vel);

	m_system->update();
}

void SoundManager::updateListener(float dt, float transform[16], float velx, float vely, float velz)
{
	if (mSilent) return;
	if (mInitFailed) return;

	//update(dt);
	FMOD_VECTOR pos = { transform[12], transform[13], transform[14] };
	FMOD_VECTOR vel = { velx, vely, velz };
	FMOD_VECTOR forward = { transform[8], transform[9], transform[10] };
	FMOD_VECTOR up = { transform[4], transform[5], transform[6] };
	//takes position, velocity, forward vector, up vector
	m_system->set3DListenerAttributes(0, &pos, &vel, &forward, &up);

	result = m_system->update();
}

SkySound SoundManager::play3DSound(std::string name, float volume, float x, float y, float z, bool echo, bool loop, float fallOffStart)
{
	if (mSilent) return NULL;

	if ("" == name) return false;
	FMOD::Sound* sound = 0;
	FMOD::Channel* soundChannel;
	result = m_system->createSound(name.c_str(), FMOD_SOFTWARE | FMOD_3D, 0, &sound);

	if (!sound)
	{
		return NULL;
	}
	
	sound->set3DMinMaxDistance(fallOffStart, 2000);
	sound->setMode(loop ? FMOD_LOOP_NORMAL : FMOD_LOOP_OFF);
	//m_system->playSound(FMOD_CHANNEL_FREE, sound, false, &soundChannel);
	
	FMOD_VECTOR pos = { x, y, z }; // z??
	FMOD_VECTOR vel = { 0, 0, 0 };
	soundChannel->setVolume(volume);
	soundChannel->set3DAttributes(&pos, &vel);

	m_system->update();

	return soundChannel;
}

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