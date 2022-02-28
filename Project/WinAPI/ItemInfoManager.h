#pragma once

#include "Enums.h"
#include "SingletonBase.h"

struct Item {
	ITEM_TYPE type;
	std::string name;
	int value;
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
	Item getItemInfo(int _id) const;
	Item getItemInfo(std::string _name) const;
};