#include "Stdafx.h"
//#include "ShootingScene.h"
//
//HRESULT ShootingScene::init(void)
//{
//	//IMAGEMANAGER->addImage("½´ÆÃ ¸Ê", "Resources/Images/BackGround/ShootingBG.bmp", WINSIZEX, WINSIZEY);
//	IMAGEMANAGER->addImage("ÀüÀå", "Resources/Images/BackGround/BattleField.bmp", WINSIZEX, WINSIZEY);
//
//	_rocket = new Rocket;
//	_rocket->init();
//
//	_em = new EnemyManager;
//	_em->init();
//
//	_em->setRocketMemoryAddress(_rocket);
//	_rocket->setEnemyManagerMemoryAddress(_em);
//
//	_missileEffect = new MissileEffect;
//	_missileEffect->init();
//
//	_beamEffect = new BeamEffect;
//	_beamEffect->init();
//
//	_x = _y = 0.0f;
//
//	wsprintf(_text, "shooting Scene");
//
//	return S_OK;
//}
//
//void ShootingScene::release(void)
//{
//	_rocket->release();
//	SAFE_DELETE(_rocket);
//
//	_em->release();
//	SAFE_DELETE(_em);
//
//	_missileEffect->release();
//	SAFE_DELETE(_missileEffect);
//
//	_beamEffect->release();
//	SAFE_DELETE(_beamEffect);
//}
//
//void ShootingScene::update(void)
//{
//	if (KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
//	{
//		SCENEMANAGER->changeScene("½ÃÀÛ");
//	}
//	_rocket->update();
//
//	_em->update();
//
//	//ÇÏ´Â°ÔÁÁÀº½À°ü
//	//_missileEffect->update();
//	//_beamEffect->update();
//
//	_y -= 2;
//
//	collision();
//}
//
//void ShootingScene::render(void)
//{
//
//	//IMAGEMANAGER->findImage("½´ÆÃ ¸Ê")->render(getMemDC());
//	RECT rc = { 0,0,WINSIZEX,WINSIZEY };
//	IMAGEMANAGER->findImage("ÀüÀå")->loopRender(getMemDC(), &rc, (int)_x, (int)_y);
//
//	_rocket->render();
//
//	_em->render();
//
//	_missileEffect->render();
//
//	_beamEffect->render();
//
//	TextOut(getMemDC(), CENTER_X, CENTER_Y, _text, (int)strlen(_text));
//}
