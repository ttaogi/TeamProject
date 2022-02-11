#include "Stdafx/stdafx.h"

#include "Player.h"

Player::Player() : Component((const Component_ID)typeid(Player).name()) { hp = 100; }

Player::~Player() { }

void Player::Init() { }

void Player::Update(HWND _hWnd) { }

void Player::LateUpdate() { }
