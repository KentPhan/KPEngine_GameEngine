#pragma once
#include "GameObject.h"
class Monster;
class Player;

class GameManager
{
private:
	GameObject* Map[20][20];
	void GetParameters();
	void MainGameLoop(Player* player, Monster* monsters);
	void PrintMap();
	void MovePlayer(Player* player, int xMagnitude, int yMagnitude);
	void MoveMonster(Monster* monsterList);

public:
	GameManager();

	void InitiateGame();
	int number_of_monsters;

	~GameManager();
};

