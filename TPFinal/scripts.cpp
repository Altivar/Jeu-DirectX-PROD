#include "scripts.h"
#include "model.h"


/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void PlayerScript::Action()
{
	ScriptComponent::Action();
	_baseModel->Translate(0, 0, 0.1f);
}


/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
void TestScript::Start()
{
	_baseModel->SetLocation(2.0f, 0, 0);
}

void TestScript::Action()
{
	ScriptComponent::Action();
	_baseModel->Rotate(0, 0.01f, 0);
}

