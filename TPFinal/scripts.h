#pragma once

#include "modelcomponent.h"

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
class PlayerScript : public ScriptComponent
{

public:
	PlayerScript(Model* model) : ScriptComponent(model){}
	virtual void Action();
};

///////////////////
//  TEST SCRIPT  //
///////////////////
class TestScript : public ScriptComponent
{
public:
	TestScript(Model* model) : ScriptComponent(model){}
	virtual void Action();
	virtual void Start();
};
