#include "Stdafx.h"
#include "SecondScene.h"

HRESULT SecondScene::init(void)
{
	IMAGEMANAGER->addImage("리듬", "Resources/Images/Background/bg3.bmp", WINSIZEX / 2, WINSIZEY);
	IMAGEMANAGER->addImage("배경 루프", "Resources/Images/Background/sweet.bmp", WINSIZEX/2, WINSIZEY/2);

	_tempSound = new TempSoundTest;
	_tempSound->init();

	_offsetX = _offsetY = 0;
	_bgSpeed = 0;

	_textBufferCnt = 0;

	_player.rc1 = RectMakeCenter(49, 703, 91, 40);
	_player.rc2 = RectMakeCenter(149, 703, 91, 40);
	_player.rc3 = RectMakeCenter(249, 703, 91, 40);
	_player.rc4 = RectMakeCenter(349, 703, 91, 40);

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].en1 = RectMakeCenter(46, 0, 100, 20);
		_enemy[i].speed1 = RND->getFromIntTo(2, 4);
		_enemy[i].die = false;
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].en2 = RectMakeCenter(149, 0, 102, 20);
		_enemy[i].speed2 = RND->getFromIntTo(3, 5);
		_enemy[i].die = false;
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].en3 = RectMakeCenter(253, 0, 100, 20);
		_enemy[i].speed3 = RND->getFromIntTo(1, 4);
		_enemy[i].die = false;
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		_enemy[i].en4 = RectMakeCenter(354, 0, 96, 20);
		_enemy[i].speed4 = RND->getFromIntTo(4, 8);
		_enemy[i].die = false;
	}

	return S_OK;
}

void SecondScene::release(void)
{
	SAFE_DELETE(_tempSound);
}

void SecondScene::update(void)
{
	_tempSound->update();

	_bgSpeed += 3;

	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].en1.top += _enemy[i].speed1;
		_enemy[i].en1.bottom += _enemy[i].speed1;

		if (_enemy[i].en1.top > WINSIZEY)
		{
			_enemy[i].en1 = RectMakeCenter(46, 0, 100, 20);
		}
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].en2.top += _enemy[i].speed2;
		_enemy[i].en2.bottom += _enemy[i].speed2;

		if (_enemy[i].en2.top > WINSIZEY)
		{
			_enemy[i].en2 = RectMakeCenter(149, 0, 102, 20);
		}
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].en3.top += _enemy[i].speed3;
		_enemy[i].en3.bottom += _enemy[i].speed3;

		if (_enemy[i].en3.top > WINSIZEY)
		{
			_enemy[i].en3 = RectMakeCenter(253, 0, 100, 20);
		}
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		_enemy[i].en4.top += _enemy[i].speed4;
		_enemy[i].en4.bottom += _enemy[i].speed4;

		if (_enemy[i].en4.top > WINSIZEY)
		{
			_enemy[i].en4 = RectMakeCenter(354, 0, 96, 20);
		}
	}

	

	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (IntersectRect(&temp, &_player.rc1, &_enemy[i].en1))
			{
				_enemy[i].en1 = RectMakeCenter(46, 0, 100, 20);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('S'))
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (IntersectRect(&temp, &_player.rc2, &_enemy[i].en2))
			{
				_enemy[i].en2 = RectMakeCenter(149, 0, 102, 20);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('D'))
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (IntersectRect(&temp, &_player.rc3, &_enemy[i].en3))
			{
				_enemy[i].en3 = RectMakeCenter(253, 0, 100, 20);
			}
		}
	}
	if (KEYMANAGER->isOnceKeyDown('F'))
	{
		for (int i = 0; i < ENEMY_MAX; i++)
		{
			if (IntersectRect(&temp, &_player.rc4, &_enemy[i].en4))
			{
				_enemy[i].en4 = RectMakeCenter(354, 0, 96, 20);
			}
		}
	}
}

void SecondScene::render(void)
{
	IMAGEMANAGER->render("리듬", getMemDC(), 0, 0);
	IMAGEMANAGER->loopRender("배경 루프", getMemDC(), &RectMake(WINSIZEX/2, 0, WINSIZEX, WINSIZEY),0, _bgSpeed);

	Rectangle(getMemDC(), _player.rc1.left, _player.rc1.top, _player.rc1.right, _player.rc1.bottom);
	Rectangle(getMemDC(), _player.rc2.left, _player.rc2.top, _player.rc2.right, _player.rc2.bottom);
	Rectangle(getMemDC(), _player.rc3.left, _player.rc3.top, _player.rc3.right, _player.rc3.bottom);
	Rectangle(getMemDC(), _player.rc4.left, _player.rc4.top, _player.rc4.right, _player.rc4.bottom);


	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		Rectangle(getMemDC(), _enemy[i].en1.left, _enemy[i].en1.top, _enemy[i].en1.right, _enemy[i].en1.bottom);
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		Rectangle(getMemDC(), _enemy[i].en2.left, _enemy[i].en2.top, _enemy[i].en2.right, _enemy[i].en2.bottom);
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		Rectangle(getMemDC(), _enemy[i].en3.left, _enemy[i].en3.top, _enemy[i].en3.right, _enemy[i].en3.bottom);
	}
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (_enemy[i].die) continue;
		Rectangle(getMemDC(), _enemy[i].en4.left, _enemy[i].en4.top, _enemy[i].en4.right, _enemy[i].en4.bottom);
	}

	// SetBkMode(): 투명하게 하는 함수 (글자 뒤로 배경이 보이게 한다.)
	/*
	SetBkMode(getMemDC(), TRANSPARENT); //기존의 하얀 바탕 날림

	char str[128];
	wsprintf(str, "기존의 폰트");
	TextOut(getMemDC(), 230, 350, str, strlen(str));

	//새로운 방법
	HFONT font;
	HFONT oldFont;
	*/
	/*
	font = CreateFont
	(
		문자 크기, 문자폭, 문자전체 기울기, 문자 방향, 문자 굵기,
		기울기 (true, false), 밑줄 (할거냐 ,말거냐), 취소선(),
		문자 세팅, 출력 정확도, 클리핑 정확도, 출력의 질, 자간, 폰트
	);

	*/
	
	/*
	font = CreateFont
	(
		70, 0, 0, 0, 600,
		0, 0, 1,
		HANGUL_CHARSET, 0, 0, 0, 0, TEXT("휴먼굴림")
	);
	
	oldFont = (HFONT)SelectObject(getMemDC(), font);

	wsprintf(str, "기존의 폰트");
	TextOut(getMemDC(), 100, 400, str, strlen(str));

	SelectObject(getMemDC(), oldFont);
	DeleteObject(font);

	LPCWSTR script = L"포기하지 않고 하다보면 너희도 좋은 프로그래머가 될수 있을거야! 오류좀 그만내고 .. From. 컴파일러";

	FONTMANAGER->drawText(getMemDC(), 30, 100, "Kostar", 25, 700, script,
		((_textBufferCnt / 5) > wcslen(script) ? wcslen(script) : (_textBufferCnt / 5)),
		RGB(255, 219, 165));
		*/

}
