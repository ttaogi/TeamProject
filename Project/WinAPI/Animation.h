#pragma once

#include "Enums.h"

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
	~Animation() { release(); }

	HRESULT init(std::string _imageKey, POINT _coordinateRevision,
		CHARACTER_STATE _state, bool _loop = false,
		bool _reverse = false, float _fps = DEFAULT_FPS);

	void reset() { frameIdx = 0; elapsedSec = 0.0f; }
	void release() { }
	void animationUpdate(bool _isPlay = true);
	void animationRender(HDC _hdc, POINT _pos);
	bool isEnd() const;

	int getFrameIdx() const { return frameIdx; }
	void setFrameIdx(int idx) { frameIdx = idx % frameVec.size(); }
	void setDefaultPlayFrame(bool _reverse = false, bool _loop = false);
	void setPlayFrame(int* _playArr = nullptr, int _arrLen = 0);
	void setPlayFrame(int _start, int _end, bool _reverse = false, bool _loop = false);
	void setFPS(float _fps) { frameUpdateSec = 1.0f / _fps; }
};