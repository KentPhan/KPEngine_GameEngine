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
	void PerformPrimaryAction(Player* player, const KPVector2 movement);
	void PrintMap();
	
	void MovePlayer(Player* player, const KPVector2 movement);
	void MoveMonsters();
	void SpawnMonster(const char* name);

public:
	GameManager();

	void InitiateGame();

	int number_of_monsters;
	

	~GameManager();
};

