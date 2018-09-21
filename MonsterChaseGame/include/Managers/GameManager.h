#pragma once
#include "../GameObjects/GameObject.h"
#include "../../../KPEngine/include/Utils/List.h"
class Monster;
class Player;

class GameManager
{
private:
	GameObject* map_[20][20];
	List<Monster*> * MonsterList;
	bool endGame = false;;
	
	const int monster_limit_ = 50;
	
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

