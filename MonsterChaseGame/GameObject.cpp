#include "pch.h"
#include "GameObject.h"
#include <iostream>


GameObject::GameObject()
{
}

char* GameObject::GetName() const
{
	return name_;
}

void GameObject::SetName(char* name)
{
	this->name_ = name;
}

void GameObject::PrintInfo() const
{
	std::cout << "Name: " << name_ << "\n";
}

char GameObject::GetSymbol()
{
	return 'U';
}

GameObject::~GameObject()
{
	delete name_;
}
