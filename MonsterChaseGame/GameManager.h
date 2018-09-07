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

public:
	GameManager();

	void InitiateGame();

	~GameManager();
};

