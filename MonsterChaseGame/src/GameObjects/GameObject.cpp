
#include <iostream>
#include "../../include/GameObjects/GameObject.h"


using namespace  KPEngine::Utils;

GameObject::GameObject()
{
	this->Position = KPVector2(0, 0);
}

char* GameObject::GetName() const
{
	return name_;
}

void GameObject::SetName(char* name)
{
	name_ = name;
}

void GameObject::PrintInfo() const
{
	std::cout << "Name: " << name_ << "\n";
}

char GameObject::GetSymbol()
{
	return 'U';
}

void GameObject::SetPosition(int x, int y)
{
	this->Position.X(x);
	this->Position.Y(y);
}


GameObject::~GameObject()
{
	delete name_;
}
