#pragma once

#include "Enums.h"
#include "SingletonBase.h"

struct Item {
	ITEM_TYPE type;
	ITEM_DETAIL detailType;
	std::string name;
	int price;
	int atk;
	int def;
	int heal;
	int range;
	Image* stripe;

	void init(ITEM_TYPE _type, ITEM_DETAIL _detailType,
		std::string _name, int _price, int _atk, int _def,
		int _heal, int _range, Image* _stripe);
};

class ItemInfoManager : public SingletonBase<ItemInfoManager> {
private:
	std::vector<Item> itemVec;
public:
	ItemInfoManager() { }
	~ItemInfoManager() { }

	HRESULT init();
	void release();

	int getItemNum() const;
	Item getItemInfo(ITEM_DETAIL _detailType) const;
	Item getItemInfo(std::string _name) const;
};
