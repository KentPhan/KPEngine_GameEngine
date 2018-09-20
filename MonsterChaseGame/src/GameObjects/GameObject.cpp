#include "pch.h"
#include <iostream>
#include "../../include/GameObjects/GameObject.h"


GameObject::GameObject()
{
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
	this->X = x;
	this->Y = y;
}


GameObject::~GameObject()
{
	delete name_;
}
