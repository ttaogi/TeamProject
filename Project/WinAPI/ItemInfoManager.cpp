#include "Stdafx.h"

#include "ItemInfoManager.h"

void Item::init(ITEM_TYPE _type, ITEM_DETAIL _detailType,
	std::string _name, int _price, int _atk, int _def,
	int _heal, int _range, Image * _stripe)
{
	type = _type;
	detailType = _detailType;
	name = _name;
	price = _price;
	atk = _atk;
	def = _def;
	heal = _heal;
	range = _range;
	stripe = _stripe;
}

/////////////////////////////////

HRESULT ItemInfoManager::init()
{
	TiXmlDocument doc;

	if (XmlManager::loadFile(doc, XML_DOC_ITEM_LIST))
	{
		TiXmlElement* root = XmlManager::firstChildElement(doc, "ROOT");
		TiXmlElement* list = XmlManager::firstChildElement(root, "list");
		int listSize = 0;

		XmlManager::getAttributeValueInt(list, "num", &listSize);

		for (int i = 0; i < listSize; ++i) {
			TiXmlElement* itemInfo = XmlManager::firstChildElement(list, "item_" + to_string(i));

			if (itemInfo == NULL) continue;

			Item item;
			int type;
			int detailType;
			string name;
			int price;
			int atk;
			int def;
			int heal;
			int range;

			XmlManager::getAttributeValueInt(itemInfo, "type", &type);
			XmlManager::getAttributeValueInt(itemInfo, "detailType", &detailType);
			XmlManager::getAttributeValue(itemInfo, "name", name);
			XmlManager::getAttributeValueInt(itemInfo, "price", &price);
			XmlManager::getAttributeValueInt(itemInfo, "atk", &atk);
			XmlManager::getAttributeValueInt(itemInfo, "def", &def);
			XmlManager::getAttributeValueInt(itemInfo, "heal", &heal);
			XmlManager::getAttributeValueInt(itemInfo, "range", &range);

			item.type = (ITEM_TYPE)type;
			item.detailType = (ITEM_DETAIL)detailType;
			item.name = name;
			item.price = price;
			item.atk = atk;
			item.def = def;
			item.heal = heal;
			item.range = range;
			item.stripe = IMAGEMANAGER->
				findImage(ItemDetailToIconKeyString(item.detailType));

			itemVec.push_back(item);
		}

		cout << "####################" << endl;
		cout << "ItemInfo Init." << endl;
		cout << "item list" << endl;
		for (auto iter = itemVec.begin(); iter != itemVec.end(); ++iter)
		{
			cout << iter->name << "(" << iter->price << ")\t["
				<< (int)iter->type << ":"
				<< (int)iter->detailType << ":"
				<< ItemDetailToIconKeyString((ITEM_DETAIL)iter->detailType)
				<< "] atk : " << iter->atk << " def : " << iter->def
				<< " heal : " << iter->heal
				<< " range : " << iter->range
				<< " stripe : " << iter->stripe << endl;
		}
		cout << "item list" << endl;
		cout << "####################" << endl;
	}
	else return E_FAIL;

	return S_OK;
}

void ItemInfoManager::release() { }

int ItemInfoManager::getItemNum() const
{
	return (int)itemVec.size();
}

Item ItemInfoManager::getItemInfo(ITEM_DETAIL _detailType) const
{
	if ((int)_detailType >= itemVec.size())
		return EMPTY_ITEM;
	else
		return itemVec[(int)_detailType];
}

Item ItemInfoManager::getItemInfo(string _name) const
{
	Item item = EMPTY_ITEM;
	for (auto iter = itemVec.begin(); iter != itemVec.end(); ++iter)
	{
		if (iter->name == _name)
		{
			item = *iter;
			break;
		}
	}
	return item;
}
