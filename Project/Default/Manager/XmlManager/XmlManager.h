#pragma once

#include "DesignPattern/SingletonBase/SingletonBase.h"

class XmlManager : public SingletonBase<XmlManager> {
private:
public:
	XmlManager();
	~XmlManager();

	HRESULT Init();
	void Release();

	void LoadXml();
	void SaveXml();
};