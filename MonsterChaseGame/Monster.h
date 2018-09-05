#pragma once
class Monster
{
private:
	char* name_;
public:
	char* GetName() const;
	void SetName(char* name);
	void PrintInfo() const;


	Monster();
	~Monster();
};

