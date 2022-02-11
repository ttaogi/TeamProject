#include "Stdafx/stdafx.h"

#include "KeyManager.h"

KeyManager::KeyManager() {
	for (int i = 0; i < KEY_MAX; ++i) {
		SetKeyDown(i, false);
		SetKeyUp(i, false);
	}
}

KeyManager::~KeyManager() { }

bool KeyManager::IsOnceKeyDown(int _key) {
	if (GetAsyncKeyState(_key) & 0x8000) {
		if (GetKeyDown()[_key] == false) {
			SetKeyDown(_key, true);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		SetKeyDown(_key, false);
		return false;
	}
}

bool KeyManager::IsOnceKeyUp(int _key) {
	if (!(GetAsyncKeyState(_key) & 0x8000)) {
		if (GetKeyDown()[_key] == true) {
			SetKeyDown(_key, false);
			return true;
		}
		else {
			return false;
		}
	}
	else {
		SetKeyDown(_key, true);
		return false;
	}
}

bool KeyManager::IsStayKeyDown(int _key) {
	if (GetAsyncKeyState(_key) & 0x8000) {
		if (GetKeyDown()[_key] == true) {
			return true;
		}
		else {
			SetKeyDown(_key, true);
			return false;
		}
	}
	else {
		SetKeyDown(_key, false);
		return false;
	}
}

bool KeyManager::IsTrigger(int _key) {
	if (GetAsyncKeyState(_key) & 0x0001) return true;
	return false;
}
