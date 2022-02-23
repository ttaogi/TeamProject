#include "Stdafx.h"
#include "KeyManager.h"

HRESULT KeyManager::init(void)
{
	for (int i = 0; i < KEY_MAX; i++)
	{
		this->setKeyDown(i, false);
		this->setKeyUp(i, false);
	}
	return S_OK;
}

bool KeyManager::isOnceKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		if (!this->getKeyDown()[key])
		{
			this->setKeyDown(key, true);
			return true;
		}
	}
	else this->setKeyDown(key, false);
	return false;
}

bool KeyManager::inOnceKeyUp(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)
	{
		this->setKeyUp(key, true);
	}
	else
	{
		if (this->getKeyUp()[key])
		{
			this->setKeyUp(key, true);
			return true;
		}
	}
	return false;
}

bool KeyManager::isStayKeyDown(int key)
{
	if (GetAsyncKeyState(key) & 0x8000)return true;
	return false;
}

bool KeyManager::isToggleKey(int key)
{
	if (GetKeyState(key) & 0x0001)return true;
	return false;
}

// a-z, space, enter, 0-9.
bool KeyManager::isOnceAnyKeyDown()
{
	for (int i = 'A'; i <= 'Z'; ++i)
		if (isOnceKeyDown(i)) return true;
	for (int i = 0x30; i <= 0x39; ++i)
		if (isOnceKeyDown(i)) return true;
	if (isOnceKeyDown(VK_SPACE)) return true;
	if (isOnceKeyDown(VK_RETURN)) return true;

	return false;
}
