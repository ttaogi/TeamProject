#include "Stdafx.h"
//#include "Rocket.h"
//#include "EnemyManager.h"
//HRESULT Rocket::init(void)
//{
//	//C  /C++ ->API
//	_image = IMAGEMANAGER->addImage("로켓", "Resources/Images/Object/Rocket.bmp",
//		52 , 64 , true, RGB(255, 0, 255));
//
//	_x = CENTER_X;
//	_y = WINSIZEY - 100;
//	
//	//슈팅 게임 -> 플레이어
//	//설계 미스 -> 경험 많이 쌓아야한다
//	//?
//	//확장성 제로
//	//코드 재사용성 또한 매우 별로
//	// ㄴ 살-> 클래스 + 함수 + 기능
//
//	_rc = RectMakeCenter((int)_x, (int)_y, _image->getWidth(), _image->getHeight());
//	//(참조한 이유)아직은 없지만 ->충돌 되었을때 사용할수 있게
//	
//	_flame = new Flame;
//	_flame->init("부스터",&_x, &_y);
//
//	_missile = new MissileM1;
//	_missile->init(5, 700);
//
//	_beam = new Beam;
//	_beam->init(5, 0.5);
//	_beamIrradiation = false;
//
//	_setWeapon = MISSILE;
//
//	_currentHp = 10;
//	_maxHp = 10;
//
//	_hpBar = new ProgressBar;
//	_hpBar->init((int)_x, (int)_y, 52 , 4 );
//
//	return S_OK;
//}
//
//void Rocket::release(void)
//{
//	_flame->release();
//	SAFE_DELETE(_flame);
//
//	_missile->release();
//	SAFE_DELETE(_missile);
//
//	_beam->release();
//	SAFE_DELETE(_beam);
//
//	_hpBar->release();
//	SAFE_DELETE(_hpBar);
//}
//
//void Rocket::update(void)
//{
//	if (KEYMANAGER->isOnceKeyDown(VK_F8))
//	{
//		//char temp[32];
//		vector<string> data;
//
//		//itoa:인티저 투 아스키 (정수형을 문자열로 반환)
//
//		/*data.push_back(itoa((int)_x, temp, 10));
//		data.push_back(itoa((int)_y, temp, 10));
//		data.push_back(itoa((int)_currentHp, temp, 10));
//		data.push_back(itoa((int)_maxHp, temp, 10));*/
//
//		data.push_back(to_string((int)_x));
//		data.push_back(to_string((int)_y));
//		data.push_back(to_string((int)_currentHp));
//		data.push_back(to_string((int)_maxHp));
//
//		TEXTDATAMANAGER->save("플레이어 상태.txt", data);
//	}
//
//	if (KEYMANAGER->isOnceKeyDown(VK_F9))
//	{
//		vector<string> vData = TEXTDATAMANAGER->load("플레이어 상태.txt");
//		_x = (float)atoi(vData[0].c_str());
//		_y = (float)atoi(vData[1].c_str());
//		_currentHp = (float)atoi(vData[2].c_str());
//		_maxHp = (float)atoi(vData[3].c_str());
//	}
//
//	if (KEYMANAGER->isOnceKeyDown('1')) hitDamage(1.0f);
//	if (KEYMANAGER->isOnceKeyDown('2')) hitDamage(-1.0f);
//
//	if (KEYMANAGER->isStayKeyDown(VK_RIGHT) && _rc.right < WINSIZEX && _beamIrradiation == false)
//	{
//		_x += ROCKET_SPEED;
//	}
//
//	if (KEYMANAGER->isStayKeyDown(VK_LEFT) && _rc.left > 0 && _beamIrradiation == false)
//	{
//		_x -= ROCKET_SPEED;
//	}
//
//	if (KEYMANAGER->isStayKeyDown(VK_UP) && _rc.top > 0)
//	{
//		_y -= ROCKET_SPEED;
//	}
//
//	if (KEYMANAGER->isStayKeyDown(VK_DOWN) && _rc.bottom < WINSIZEY)
//	{
//		_y += ROCKET_SPEED;
//	}
//
//	if (KEYMANAGER->isOnceKeyDown(VK_F1))
//	{
//		_setWeapon = MISSILE;
//	}
//	
//	if (KEYMANAGER->isOnceKeyDown(VK_F2))
//	{
//		_setWeapon = BEAM;
//	}
//
//	switch (_setWeapon)
//	{
//	case MISSILE:
//		if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
//		{
//			_missile->fire(_x, _y - 60);
//		}
//		break;
//
//	case BEAM:
//		if (KEYMANAGER->isStayKeyDown(VK_SPACE))
//		{
//			_beamIrradiation = true;
//			_beam->fire(_x, _y - 430);
//		}
//		else _beamIrradiation = false;
//		break;
//	}
//	
//	_rc = RectMakeCenter((int)_x, (int)_y, _image->getWidth(), _image->getHeight());
//
//	_flame->update();
//	_missile->update();
//	_beam->update();
//
//	//collision();
//
//	_hpBar->setX((int)(_x - (_rc.right - _rc.left) / 2));
//	_hpBar->setY((int)(_y - 10 - (_rc.bottom - _rc.top) / 2));
//	_hpBar->update();
//	_hpBar->setGauge(_currentHp, _maxHp);
//}
//
//void Rocket::render(void)
//{
//	_image->render(getMemDC(), _rc.left, _rc.top);
//	_flame->render();
//	_missile->render();
//	_beam->render();
//	_hpBar->render();
//}
//
//void Rocket::collision(void)
//{
//	for (int i = 0; i < _missile->getBullet().size(); i++)
//	{
//		for (int j = 0; j < _em->getMinions().size(); j++)
//		{
//			RECT rc;
//			if (IntersectRect(&rc, &_missile->getBullet()[i].rc,
//				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
//			{
//				_missile->removeBullet(i);
//				_em->removeMinion(j);
//				break;
//			}
//		}
//	}
//
//	for (int i = 0; i < _beam->getBullet().size(); i++)
//	{
//		for (int j = 0; j < _em->getMinions().size(); j++)
//		{
//			RECT rc;
//			if (IntersectRect(&rc, &_beam->getBullet()[i].rc,
//				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
//			{
//				_em->removeMinion(j);
//				break;
//			}
//		}
//	}
//
//}
//
//void Rocket::removeMissile(int arrNum)
//{
//	_missile->removeBullet(arrNum);
//}
//
//
