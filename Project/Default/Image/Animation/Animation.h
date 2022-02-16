#pragma once

#include "Utility/Enums.h"

#define DEFAULT_FPS		60

class Animation
{
private:
	int frameIdx;
	float frameUpdateSec;
	float elapsedSec;
	bool loop;

	CHARACTER_STATE state;
	Image* image;
	POINT coordinateRevision;
	std::vector<POINT> frameVec;
	std::vector<int> playVec;
public:
	Animation();
	~Animation() { Release(); }

	HRESULT Init(std::wstring _imageKey, POINT _coordinateRevision,
		CHARACTER_STATE _state, bool _loop = false,
		bool _reverse = false, float _fps = 60.0f);

	void Reset() { frameIdx = 0; elapsedSec = 0.0f; }
	void Release() { }
	void AnimationUpdate(bool _isPlay = true);
	void AnimationRender(HDC _hdc, POINT _pos);
	bool IsEnd() const;

	int GetFrameIdx() const { return frameIdx; }
	void SetDefaultPlayFrame(bool _reverse = false, bool _loop = false);
	void SetPlayFrame(int* _playArr = nullptr, int _arrLen = 0);
	void SetPlayFrame(int _start, int _end, bool _reverse = false, bool _loop = false);
	void SetFPS(float _fps) { frameUpdateSec = 1.0f / _fps; }
};