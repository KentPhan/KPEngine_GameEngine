#pragma once
class GameObject
{

protected:
	char* name_;

public:
	char* GetName() const;
	void SetName(char* name);
	virtual void PrintInfo() const;

	int X;
	int Y;

	GameObject();
	~GameObject();
};

