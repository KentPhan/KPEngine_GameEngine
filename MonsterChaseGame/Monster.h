#pragma once
#include "GameObject.h"

class Monster : public GameObject
{
public:
	Monster();
	void PrintInfo() const override;
	~Monster();
};

