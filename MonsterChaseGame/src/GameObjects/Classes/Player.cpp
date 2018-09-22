
#include <iostream>
#include "../../../include/GameObjects/Classes/Player.h"

using namespace KPEngine::Utils;

Player::Player()
{
	
}

void Player::PrintInfo() const
{
	std::cout << "Player \"" << name_->Get() << "\" at [" << this->Position.X() << "," << this->Position.Y() << "]\n";
}

char Player::GetSymbol()
{
	return 'P';
}

Player::~Player()
{
}
