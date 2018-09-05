#include "pch.h"
#include "Monster.h"
#include <iostream>


Monster::Monster()
{
}


char* Monster::GetName() const
{
	return name_;
}

void Monster::SetName(char* name)
{
	this->name_ = name;
}

void Monster::PrintInfo() const
{
	std::cout << "Name: " << name_ << "\n";
}

Monster::~Monster()
{
	delete name_;
}
