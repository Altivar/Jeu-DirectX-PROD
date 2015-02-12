#include "scripts.h"
#include "model.h"

#define PI 3.141592f

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void PlayerScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	//_baseModel->Translate(0, 0, 5.0f * args.GetDeltaTime() );

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


/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void TestScript::Start()
{
	_baseModel->SetScale(5.0f);
	_baseModel->Translate(3.0, 0, 0.5f);
}
void TestScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	//_baseModel->Rotate(0, PI * args.GetDeltaTime(), 0);
}

void TestScript2::Start()
{
	_baseModel->SetLocation(-3.0f, 0, 0);
}
void TestScript2::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	//_baseModel->Rotate(0, PI * args.GetDeltaTime(), 0);
}