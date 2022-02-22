#include "Stdafx.h"
#include "ShootingScene.h"

void ShootingScene::collision(void)
{
	for (int i = 0; i < _rocket->getMissile()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getMissile()->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect())) 
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_missileEffect->show(rc);

				_rocket->removeMissile(i);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _rocket->getBeam()->getBullet().size(); i++)
	{
		for (int j = 0; j < _em->getMinions().size(); j++)
		{
			RECT rc;
			if (IntersectRect(&rc, &_rocket->getBeam()->getBullet()[i].rc,
				//&_em->getMinions()[j]->getRect()))
				&CollisionAreaResizing(_em->getMinions()[j]->getRect(), 40, 30)))
			{
				_beamEffect->show(rc);
				_em->removeMinion(j);
				break;
			}
		}
	}

	for (int i = 0; i < _em->getBullet()->getBullet().size(); i++)
	{
		RECT rc;
		if (IntersectRect(&rc, &_em->getBullet()->getBullet()[i].rc,
			&_rocket->getRect()))
		{
			_em->getBullet()->removeBullet(i);
			_rocket->hitDamage(2.0f);
		}
	}
}