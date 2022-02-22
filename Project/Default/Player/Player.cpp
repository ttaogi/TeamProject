#include "Stdafx/stdafx.h"

#include "Player.h"

#include "DesignPattern/ComponentBase/Component/Rendered/RenderedAnimator/RenderedAnimator.h"

Player::Player() : Component((const Component_ID)typeid(Player).name()) { hp = 100; }

Player::~Player() { }

void Player::Init() { }

void Player::Update() { }

void Player::LateUpdate() { }
