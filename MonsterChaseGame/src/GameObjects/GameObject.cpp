
#include <iostream>
#include "../../include/GameObjects/GameObject.h"


using namespace  KPEngine::Utils;

GameObject::GameObject()
{
	this->Position = KPVector2(0, 0);
}

char* GameObject::GetName() const
{
	return name_->Get();
}

void GameObject::SetName(const char* name)
{
	if (name_ != nullptr)
		delete name_;
	name_ = new KPString(name);
}

void GameObject::PrintInfo() const
{
	std::cout << "Name: " << name_->Get() << "\n";
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
