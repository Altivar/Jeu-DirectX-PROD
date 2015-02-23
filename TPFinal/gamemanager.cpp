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
	_timeBetweenObstacles = 2.0f;
	_obstacleSpeed = 3.0f;
	_score = 0;

	Model* m1 = ModelsSingleton::Instance()->Instanciate(Caterpie, Point3(0.0f, 1.0f, -1.0f), Point3(0.0f, 3.141592f/2.0f, 0.0f));
	m1->SetScale(0.2f);
	m1->AddComponent(new ColliderComponent(m1));
	m1->AddComponent(new PlayerScript(m1));

	Model* m2 = ModelsSingleton::Instance()->Instanciate(Pokeball);
	m2->AddComponent(new ObstacleScript(m2));
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
	float timeToWait = _timeBetweenObstacles - (_score / 500.0f)*0.1f;
	if( timeToWait < 1.0f )
		timeToWait = 1.0f;
	if( _timer >= timeToWait )
	{
		Model* model = ModelsSingleton::Instance()->Instanciate(Pokeball);
		model->AddComponent(new ObstacleScript(model));

		_timer -= _timeBetweenObstacles;
	}

}

void GameManager::ObstaclePassed()
{
	int pointsGained = (int)(_obstacleSpeed * 10.0f);
	_score += pointsGained;

	_obstacleSpeed += 0.2f;
}

