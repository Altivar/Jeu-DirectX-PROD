#include "scripts.h"
#include "modelssingleton.h"
#include "gamemanager.h"
#include <ctime>


// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

#define PI 3.141592f

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void PlayerScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	if(GetAsyncKeyState(VK_LEFT))
	{
		_baseModel->Translate(-3.0f * args.GetDeltaTime(), 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		_baseModel->Translate(3.0f * args.GetDeltaTime(), 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_UP))
	{
		_baseModel->Translate(0.0f, 3.0f * args.GetDeltaTime(), 0.0f);
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		_baseModel->Translate(0.0f, -3.0f * args.GetDeltaTime(), 0.0f);
	}
}

void PlayerScript::Collide(EventArgs args)
{
	_baseModel->SetTexture(".\\Resources\\redstone_block.png");
}


///////////////////////
//  OBSTACLE SCRIPT  //
///////////////////////
void ObstacleScript::Start()
{
	
	// random X position [-3;3]
	std::srand((int)std::time(0));
	float randStartPosition = (float)(std::rand() % 600);
	randStartPosition -= 300;
	randStartPosition /= 100;

	_baseModel->SetLocation(randStartPosition, 0.0f, 10.0f);

}

void ObstacleScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	_baseModel->Translate(0, 0, -GameManager::Instance()->GetObstacleSpeed() * args.GetDeltaTime() );

	if( _baseModel->_location.z <= -2.0f )
	{
		ModelsSingleton::Instance()->Destroy(_baseModel);
		GameManager::Instance()->ObstaclePassed();
	}
}




///////////////////
//  TEST SCRIPT  //
///////////////////
void TestScript::Start()
{
	_baseModel->SetScale(4.8f);
}
void TestScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	_baseModel->Rotate(0.0f, PI*args.GetDeltaTime(), 0.0f);
}

void TestScript2::Start()
{
	//_baseModel->SetLocation(-3.0f, 0, 0);
}
void TestScript2::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	//_baseModel->Rotate(0, PI * args.GetDeltaTime(), 0);
}