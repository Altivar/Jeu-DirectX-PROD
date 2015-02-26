#pragma once
#include "args.h"

struct Model;

class GameManager
{
public:
	static GameManager* Instance();
	static void ReleaseInstance();

	void UpdateGame(UpdateArgs args);
	
	float GetObstacleSpeed() { return _obstacleSpeed; }
	void ObstaclePassed();
	int GetScore() { return _score; }
	void Pause();
	float GetTimeScale() { return _timeScale; }

private:
	GameManager(void);
	~GameManager(void);
	
	static GameManager* _instance;

	float _timer;
	float _timeBetweenObstacles;
	float _obstacleSpeed;
	int _score;

	float _timeScale;

	Model* _player;
};

