#pragma once
#include "../GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	void PrintInfo() const override;
	char GetSymbol() override;
	~Monster();
};

