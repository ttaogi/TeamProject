#pragma once
#include "GameNode.h"

//Enemy (�θ� Ŭ����): �� Ŭ������ ������� ����, �Ϲ� ���͵��� ����ٰ� ������ ������ ������ �����Ҷ� �����ϰ� ����°� ����
class Enemy : public GameNode
{
protected:
	Image* _image;
	RECT _rc;

	int _currentFrameX;
	int _currentFrameY;

	float _x, _y;
	float _rndTimeCount;
	float _worldTimeCount;

	float _rndFireCount;
	float _bulletFireCount;

public:
	HRESULT init(void);
	HRESULT init(const char* imageName, POINT position);
	void release(void);
	void update(void);
	void render(void);

	void move(void);
	void draw(void);
	void animation(void);

	bool bulletCountFire(void);

	RECT getRect(void) { return _rc; }

	Enemy(void);
	~Enemy(void) {}
};

