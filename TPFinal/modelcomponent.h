#pragma once
#include "args.h"


struct Model;

/////////////////////////////
//  MODEL COMPONENT CLASS  //
/////////////////////////////
class ModelComponent
{

public:
	ModelComponent(Model* model);
	virtual void Action(UpdateArgs& args) = 0;

protected:
	Model* _baseModel;

};


//////////////////////////////
//  SCRIPT COMPONENT CLASS  //
//////////////////////////////
class ScriptComponent : public ModelComponent
{

public:
	ScriptComponent(Model* model);
	~ScriptComponent(void);
	virtual void Action(UpdateArgs& args) = 0;

protected:
	bool _hasStarted;

	virtual void Start();
	virtual void End();
	virtual void OnCollisionEnter(CollisionArgs args);

};


