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
	virtual void Collide(EventArgs args);
};

///////////////////////
//  OBSTACLE SCRIPT  //
///////////////////////
class ObstacleScript : public ScriptComponent
{
private:
	virtual void Start();
	bool isDestroyed;
public:
	ObstacleScript(Model* model) : ScriptComponent(model){}
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
class TestScript2 : public ScriptComponent
{
public:
	TestScript2(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);
	virtual void Start();
};
