#include "modelcomponent.h"
#include "model.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG



/////////////////////////////
//  MODEL COMPONENT CLASS  //
/////////////////////////////
ModelComponent::ModelComponent(Model* model)
{
	_baseModel = model;
}


//////////////////////////////
//  SCRIPT COMPONENT CLASS  //
//////////////////////////////
ScriptComponent::ScriptComponent(Model* model)
	: ModelComponent(model)
{
	this->_hasStarted = false;
}

ScriptComponent::~ScriptComponent(void)
{
	this->End();
}

void ScriptComponent::Start()
{
}

void ScriptComponent::Action(UpdateArgs& args)
{
	if( !this->_hasStarted )
	{
		this->Start();
		this->_hasStarted = true;
	}
}

void ScriptComponent::End()
{
}

void ScriptComponent::OnCollisionEnter(CollisionArgs args)
{
}


