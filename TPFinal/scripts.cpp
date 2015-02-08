#include "scripts.h"
#include "model.h"

#define PI 3.141592f

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void PlayerScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	_baseModel->Translate(0, 0, 5.0f * args.GetDeltaTime() );
}


/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void TestScript::Start()
{
	_baseModel->SetLocation(2.0f, 0, 0);
}

void TestScript::Action(UpdateArgs& args)
{
	ScriptComponent::Action(args);
	_baseModel->Rotate(0, PI * args.GetDeltaTime(), 0);
}

