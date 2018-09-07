#pragma once
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
	
	int X;
	int Y;
	bool empty = true;
	GameObject();
	~GameObject();
};

