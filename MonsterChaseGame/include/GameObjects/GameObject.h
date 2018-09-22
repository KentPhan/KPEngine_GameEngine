#pragma once
#include "GameObjectType.h"
#include "include/Utils/KPVector2.h"

class GameObject
{
	
protected:
	char* name_;
	
	
public:
	char* GetName() const;
	void SetName(char* name);
	virtual void PrintInfo() const;
	virtual char GetSymbol();
	void SetPosition(int x, int y);

	KPEngine::Utils::KPVector2 Position;
	GameObjectType Type;

	bool empty = true;
	GameObject();
	~GameObject();
};

