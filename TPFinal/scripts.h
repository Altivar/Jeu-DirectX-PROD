#pragma once

#include "modelcomponent.h"

/////////////////////
//  PLAYER SCRIPT  //
/////////////////////
class PlayerScript : public ScriptComponent
{
private:
	float yAngle;
	virtual void Start();
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
protected:
	virtual void Start();
	bool isDestroyed;
public:
	ObstacleScript(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);

	float speed;
};

class HomingObstacleScript : public ObstacleScript
{
public:
	HomingObstacleScript(Model* model) : ObstacleScript(model){}
	virtual void Action(UpdateArgs& args);

	Model* target;
	
};

////////////////////
//  WATER SCRIPT  //
////////////////////
class WaterScript : public ScriptComponent
{
public:
	WaterScript(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);
};

///////////////////
//  FISH SCRIPT  //
///////////////////
class FishScript : public ScriptComponent
{
	virtual void Start();
	bool _fishAnimLaucnhed;
	float _yPos;
	float _xPos;
	float _zAngle;
public:
	FishScript(Model* model) : ScriptComponent(model){}
	virtual void Action(UpdateArgs& args);

	void LaunchFishAnimation();
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
