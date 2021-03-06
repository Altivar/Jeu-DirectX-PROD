#include "scripts.h"
#include "modelssingleton.h"
#include "gamemanager.h"
#include "guimanager.h"


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

	_baseModel->SetScale(0.15f);
	_baseModel->SetLocation(0, 0.5f, -0.5f);
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
	std::string strToFind = "ballImage.png";
	if( args.strArgs.find(strToFind) != std::string::npos )
	{
		_baseModel->SetTexture(".\\Resources\\redstone_block.png");
		GUIManager::Instance()->PlayerCollided(args.strArgs);
	}
}



///////////////////////
//  OBSTACLE SCRIPT  //
///////////////////////
void ObstacleScript::Start()
{
	isDestroyed = false;
	
	_baseModel->SetScale(0.4f);

	float randStartPosition = (float)(std::rand() % 1000);
	randStartPosition -= 500;
	randStartPosition /= 500;
	randStartPosition *= 3.5f;

	_baseModel->SetLocation(randStartPosition, 1.0f, 16.0f);

}

void ObstacleScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);

	_baseModel->Translate(0, 0, -speed * args.GetDeltaTime() );
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

void HomingObstacleScript::Action(UpdateArgs& args)
{
	ObstacleScript::Action(args);

	if( target == NULL )
		return;

	if( target->_location.x > _baseModel->_location.x )
		_baseModel->Translate(1.5f*args.GetDeltaTime(), 0, 0);
	else
		_baseModel->Translate(-1.5f*args.GetDeltaTime(), 0, 0);
}

////////////////////
//  WATER SCRIPT  //
////////////////////
void WaterScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	
	_baseModel->Translate(-1.0f * args.GetDeltaTime(), 0, 0);
	if( _baseModel->_location.x < -5.0f )
		_baseModel->Translate(4.8f, 0, 0);
}

///////////////////
//  FISH SCRIPT  //
///////////////////
void FishScript::Start()
{
	_fishAnimLaucnhed = false;
	_baseModel->SetLocation(0.0f, -3.0f, -3.0f);
	//_baseModel->SetRotation(3.14159265f,-3.14159265f/2,-3.14159265f/2);
	_baseModel->SetRotation(PI, -PI/2, PI);
}

void FishScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	
	if( !_fishAnimLaucnhed )
		return;

	_yPos += args.GetDeltaTime()*2.0f;
	_zAngle += PI * args.GetDeltaTime() / 2.4f;
	_xPos -= args.GetDeltaTime()*2.0f;
	_baseModel->SetLocation(_xPos, -pow(_yPos,2)-0.5f, -3.0f);
	_baseModel->SetRotation(0, -PI/2, _zAngle);

	if( _yPos >= 3.0f )
		_fishAnimLaucnhed = false;
}

void FishScript::LaunchFishAnimation()
{
	_fishAnimLaucnhed = true;
	_yPos = -2.5f;
	_zAngle = -PI/1.8f;

	float randStartPosition = (float)(std::rand() % 6000);
	randStartPosition = randStartPosition / 1000.0f;
	_xPos = randStartPosition;

	int randShininess = (std::rand() % 100);
	if( randShininess < 10 )
		_baseModel->SetTexture(".\\Resources\\magicarpe_Shiney_UV.png");
	else
		_baseModel->SetTexture(".\\Resources\\magicarpe_UV.png");
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