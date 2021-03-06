#pragma once

#include "SingletonBase.h"

class PlayerInfoManager : public SingletonBase<PlayerInfoManager> {
private:
	int money;
	int hp;
	int hpMax;
	Item shovel;
	Item attack;
	Item body;
	Item head;
	Item torch;
	Item heal;
	Item bomb;
public:
	PlayerInfoManager() { }
	~PlayerInfoManager() { }

	HRESULT init();
	void release();

	void isAttacked(int _dmg);

	int getMoney() const;
	void setMoney(int _money);
	Item getShovel() const;
	void setShovel(Item _shovel);
	Item getAttack() const;
	void setAttack(Item _attack);
	Item getBody() const;
	void setBody(Item _body);
	Item getHead() const;
	void setHead(Item _head);
	Item getTorch() const;
	void setTorch(Item _torch);
	Item getHeal() const;
	void setHeal(Item _heal);
	Item getBomb() const;
	void setBomb(Item _bomb);
	int getHp() const;
	void setHp(int _hp);
	int getHpMax() const;
	int getViewDistance();
};