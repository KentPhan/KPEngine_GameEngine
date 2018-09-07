#pragma once
#include "GameObject.h"
class Monster;
class Player;

class GameManager
{
private:
	GameObject* map_[20][20];
	Monster* MonsterList;
	
	const int monster_limit_ = 50;
	
	
	int monster_allocation_location_ = 0;
	const int MONSTER_LIST_SIZE = 1000;

	void GetParameters();
	void MainGameLoop(Player* player);
	void PrintMap();
	void MovePlayer(Player* player, int xMagnitude, int yMagnitude);
	void MoveMonsters();
	void SpawnMonster(char* name);

public:
	GameManager();

	void InitiateGame();

	int number_of_monsters;
	

	~GameManager();
};

