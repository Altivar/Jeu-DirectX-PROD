#pragma once

#include "model.h"
#include <list>

////      ///////      ////
//	DECLARE MODELS ENUM  //
////      ///////      ////
enum ModelName
{
	Cube = 0,
	Torus,
	Book,
	Thing
};

class ModelsSingleton
{
public:
	static ModelsSingleton* Instance();
	static void ReleaseInstance();

	std::list<Model*> _models;

	// models count from beginning of the app
	int _modelsCount;

	Model _modelCube;
	Model _modelTorus;
	Model _modelThing;
	Model _modelBook;

private:
	ModelsSingleton(void);
	~ModelsSingleton(void);

	static ModelsSingleton* _instance;

	// add model to the render list
	Model* Instanciate(ModelName modelName);
	Model* Instanciate(ModelName modelName, Point3 position, Point3 rotation);

	
};

