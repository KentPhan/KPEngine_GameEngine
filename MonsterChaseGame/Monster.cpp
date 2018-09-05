#include "pch.h"
#include "Monster.h"




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

Monster::~Monster()
{
	delete name_;
}
