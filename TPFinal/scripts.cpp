#include "scripts.h"
#include "modelssingleton.h"
#include "gamemanager.h"


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
		_baseModel->Translate(-5.0f * args.GetDeltaTime(), 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_RIGHT))
	{
		_baseModel->Translate(5.0f * args.GetDeltaTime(), 0.0f, 0.0f);
	}
	if(GetAsyncKeyState(VK_UP))
	{
		_baseModel->Translate(0.0f, 5.0f * args.GetDeltaTime(), 0.0f);
	}
	if(GetAsyncKeyState(VK_DOWN))
	{
		_baseModel->Translate(0.0f, -5.0f * args.GetDeltaTime(), 0.0f);
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
	isDestroyed = false;
	
	float randStartPosition = (float)(std::rand() % 1000);
	randStartPosition -= 500;
	randStartPosition /= 100;

	_baseModel->SetLocation(randStartPosition, 0.0f, 30.0f);

}

void ObstacleScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	_baseModel->Translate(0, 0, -GameManager::Instance()->GetObstacleSpeed() * args.GetDeltaTime() );

	if( isDestroyed )
		return;

	if( _baseModel->_location.z <= -2.0f )
	{
		ModelsSingleton::Instance()->Destroy(_baseModel, 5.0f);
		GameManager::Instance()->ObstaclePassed();
		isDestroyed = true;
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