#include "gamemanager.h"
#include "modelssingleton.h"
#include "scripts.h"
#include <ctime>


// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG


GameManager* GameManager::_instance = NULL;


GameManager::GameManager(void)
{
	// init random 
	std::srand((int)time(0));
	
	_timer = 0.0f;
	_timeBetweenObstacles = 3.5f;
	_obstacleSpeed = 7.0f;
	_score = 1;

	// time scale
	_timeScale = 1.0f;

	// player
	_player = ModelsSingleton::Instance()->Instanciate(Caterpie, Point3(0.0f, 1.0f, -1.0f), Point3(0.0f, 3.141592f/2.0f, 0.0f));
	_player->SetScale(0.2f);
	_player->AddComponent(new ColliderComponent(_player));
	_player->AddComponent(new PlayerScript(_player));

	// ground
	Model* m2 = ModelsSingleton::Instance()->Instanciate(Ground);
	m2->SetScale(10.0f);
	m2->SetLocation(0, 0, 9.0f);
	m2->_tilingX = 15;
	m2->_tilingY = 15;
	Model* m7 = ModelsSingleton::Instance()->Instanciate(Ground);
	m7->SetScale(6.0f);
	m7->SetLocation(0, -3.0f, -3.0f);
	m7->SetRotation(-3.141592f/6, 0, 0);
	m7->SetTexture(".\\Resources\\rocktexture.png");
	m7->_tilingX = 10;
	Model* m8 = ModelsSingleton::Instance()->Instanciate(Ground);
	m8->SetScale(6.0f);
	m8->SetLocation(0, -3.0f, 0);
	m8->_tilingX = 15;
	m8->_tilingY = 15;
	m8->SetTexture(".\\Resources\\watertexture.png");
	m8->AddComponent(new WaterScript(m8));

	// local obstacles
	Model* m3 = ModelsSingleton::Instance()->Instanciate(Rock, Point3(-5.2f, 1.0f, 0), Point3(0,1.3f,0));
	Model* m4 = ModelsSingleton::Instance()->Instanciate(Rock, Point3(5.7f, 1.0f, 0), Point3(0,-0.25f,0));
	m3->SetScale(0.4f);
	m4->SetScale(0.7f);
	m3->SetTexture(".\\Resources\\rocktexture2.png");
	m4->SetTexture(".\\Resources\\rocktexture2.png");

	// for the background
	Model* m5 = ModelsSingleton::Instance()->Instanciate(Fond);
	m5->SetLocation(0, -2.0f, 15.0f);
	m5->SetScale(2.0f);
	m5->SetTexture(".\\Resources\\fond.png");
	m5->_tilingX = 3;
	m5->_tilingY = 3;
	Model* m6 = ModelsSingleton::Instance()->Instanciate(Fond);
	m6->SetLocation(0, -0.5f, 14.0f);
	m6->SetScale(0.3f);
	m6->SetTexture(".\\Resources\\ennemy.png");


}

GameManager::~GameManager(void)
{
}

//////////////////////////
//  SINGLETON INSTANCE  //
//////////////////////////
GameManager* GameManager::Instance()
{
	if( _instance == NULL )
		_instance = new GameManager();
	return _instance;
}

void GameManager::ReleaseInstance()
{
	delete _instance;
	_instance = NULL;
}

////////////////////////////
//  GAME MANAGER METHODS  //
////////////////////////////
void GameManager::UpdateGame(UpdateArgs args)
{

	_timer += args.GetDeltaTime();
	float timeToWait = _timeBetweenObstacles - (_score / 500.0f);
	if( timeToWait < 1.0f )
		timeToWait = 1.0f;
	if( _timer >= timeToWait )
	{

		Model* model;
		float rand = (float)(std::rand() % _score);
		if( rand > 2500 )
		{
			HomingObstacleScript* os;
			model = ModelsSingleton::Instance()->Instanciate(Pokeball);
			model->SetTexture(".\\Resources\\masterball.png");
			os = new HomingObstacleScript(model);
			os->target = _player;
			os->speed = 14.0f;
			model->AddComponent(os);
		}
		else
		{
			ObstacleScript* os;
			if ( rand > 900 )
			{
				model = ModelsSingleton::Instance()->Instanciate(Pokeball);
				model->SetTexture(".\\Resources\\filetball.png");
				os = new ObstacleScript(model);
				os->speed = 12.0f;
			}
			else if ( rand > 700 )
			{
				model = ModelsSingleton::Instance()->Instanciate(Pokeball);
				model->SetTexture(".\\Resources\\hyperball.png");
				os = new ObstacleScript(model);
				os->speed = 10.0f;
			}
			else if ( rand > 200 )
			{
				model = ModelsSingleton::Instance()->Instanciate(Pokeball);
				model->SetTexture(".\\Resources\\superball.png");
				os = new ObstacleScript(model);
				os->speed = 8.0f;
			}
			else
			{
				model = ModelsSingleton::Instance()->Instanciate(Pokeball);
				model->SetTexture(".\\Resources\\pokeball.png");
				os = new ObstacleScript(model);
				os->speed = 6.0f;
			}
			model->AddComponent(os);
		}

		

		_timer -= timeToWait;

	}

}

void GameManager::ObstaclePassed()
{
	int pointsGained = (int)(_obstacleSpeed * 10.0f);
	_score += pointsGained;

	_obstacleSpeed += 0.5f;
}

void GameManager::Pause()
{
	if( _timeScale != 1.0f )
		_timeScale = 1.0f;
	else
		_timeScale = 0.0f;
}