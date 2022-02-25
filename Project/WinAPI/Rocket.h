#pragma once
//#include "GameNode.h"
//#include "Flame.h"
//#include "Bullets.h"
//#include "ProgressBar.h"
//
//#define ROCKET_SPEED 3.0f
//
////참조를 위해서 전방선언
//class EnemyManager;
//
//enum EWeapon
//{
//	MISSILE, BEAM
//};
//
//class Rocket : public GameNode
//{
//private:
//	Image* _image;
//	Flame* _flame;
//	MissileM1* _missile;
//	Beam* _beam;
//	ProgressBar*_hpBar;
//	//! Not Member
//	EnemyManager* _em;
//
//	EWeapon _setWeapon;
//
//	RECT _rc;
//	float _x, _y; //이걸 주고받고..
//	float _currentHp;
//	float _maxHp;
//
//	bool _beamIrradiation;
//
//public:
//	HRESULT init(void);
//	void release(void);
//	void update(void);
//	void render(void);
//
//	void removeMissile(int arrNum);
//
//	void collision(void);
//	void setEnemyManagerMemoryAddress(EnemyManager* em) { _em = em; }
//
//
//	MissileM1* getMissile(void) { return _missile; }
//	Beam* getBeam(void) { return _beam; }
//
//	//내 위치정보 빼주기 위함
//	POINT getPosition(void) { return PointMake((int)_x, (int)_y); }
//	RECT getRect(void) { return _rc; }
//
//	inline void hitDamage(float damage)
//	{
//		if (_currentHp <= 0)
//		{
//			_currentHp = 0;
//			return;
//		}
//		_currentHp -= damage;
//	}
//	
//
//	Rocket() {}
//	~Rocket() {}
//};
//
