#pragma once
#include "GameObject.h"
class Monster;
class Player;

class GameManager
{
private:
	void GetParameters();
	void MainGameLoop();
	void MovePlayer();

	GameObject *Map[10][10];
public:
	GameManager();

	void InitiateGame();

	~GameManager();
};

