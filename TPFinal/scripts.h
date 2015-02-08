#pragma once

#include "modelcomponent.h"

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
class PlayerScript : public ScriptComponent
{

public:
	PlayerScript(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);
};

///////////////////
//  TEST SCRIPT  //
///////////////////
class TestScript : public ScriptComponent
{
public:
	TestScript(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);
	virtual void Start();
};
