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
void PlayerScript::Start()
{
	yAngle = 0.0f;

	_baseModel->SetLocation(0, 0.5f, 0);
}

void PlayerScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	if(GetAsyncKeyState(VK_LEFT))
	{
		yAngle -= PI/2*args.GetDeltaTime();
		_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
	}
	else if(GetAsyncKeyState(VK_RIGHT))
	{
		yAngle += PI/2*args.GetDeltaTime();
		_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
	}
	else // if there is no input
	{
		if( yAngle == 0.0f )
		{
			return;
		}
		else if( yAngle > 0.05f )
		{
			yAngle -= (PI/2*args.GetDeltaTime() > yAngle) ? yAngle : PI/2*args.GetDeltaTime();
			_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
		}
		else if( yAngle < -0.05f )
		{
			yAngle += (PI/2*args.GetDeltaTime() > -yAngle) ? -yAngle : PI/2*args.GetDeltaTime();
			_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
		}
		else
		{
			yAngle = 0.0f;
			_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
		}
	}
	if( yAngle > PI/6.0f )
	{
		yAngle = PI/6.0f;
		_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
	}
	if( yAngle < -PI/6.0f )
	{
		yAngle = -PI/6.0f;
		_baseModel->SetRotation(Point3(0, 1.0f, 0), yAngle+PI/2);
	}

	float newX = 5.0f * (yAngle/(PI/6.0f)) * args.GetDeltaTime() + _baseModel->_location.x;
	if( newX > 3.5f )
		newX = 3.5f;
	if( newX < -3.5f )
		newX = -3.5f;
	_baseModel->SetLocation(newX, _baseModel->_location.y, _baseModel->_location.z);
	
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
	
	_baseModel->SetScale(0.7f);

	float randStartPosition = (float)(std::rand() % 1000);
	randStartPosition -= 500;
	randStartPosition /= 500;
	randStartPosition *= 3.5f;

	_baseModel->SetLocation(randStartPosition, 1.0f, 30.0f);

}

void ObstacleScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	_baseModel->Translate(0, 0, -GameManager::Instance()->GetObstacleSpeed() * args.GetDeltaTime() );
	_baseModel->Rotate(0, 2*PI*args.GetDeltaTime(), 0);

	if( isDestroyed )
		return;

	if( _baseModel->_location.z <= -2.0f )
	{
		ModelsSingleton::Instance()->Destroy(_baseModel, 1.0f);
		GameManager::Instance()->ObstaclePassed();
		isDestroyed = true;
	}
}



///////////////////
//  TEST SCRIPT  //
///////////////////
void TestScript::Start()
{
	_baseModel->SetScale(0.8f);
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