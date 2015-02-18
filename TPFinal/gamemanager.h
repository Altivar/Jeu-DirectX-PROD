#pragma once
#include "args.h"

class GameManager
{
public:
	static GameManager* Instance();
	static void ReleaseInstance();

	void UpdateGame(UpdateArgs args);
	
	float GetObstacleSpeed() { return _obstacleSpeed; }
	void ObstaclePassed();
	int GetScore() { return _score; }

private:
	GameManager(void);
	~GameManager(void);
	
	static GameManager* _instance;

	float _timer;
	float _timeBetweenObstacles;
	float _obstacleSpeed;
	int _score;
};

