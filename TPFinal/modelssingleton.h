#pragma once

#include "model.h"
#include <list>
#include <map>

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
	
	// add model to the render list
	Model* Instanciate(ModelName modelName);
	Model* Instanciate(ModelName modelName, Point3 position, Point3 rotation);
	// remove model from render list
	void Destroy(Model* model);
	void Destroy(Model* model, float timer);
	void CleanListOfModels(UpdateArgs args);

	std::list<Model*> _models;
	std::map<Model*, float> _modelsToRemove;

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


	
};

