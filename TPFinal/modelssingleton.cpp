#include "modelssingleton.h"
#include "scripts.h"

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

ModelsSingleton ModelsSingleton::_instance = ModelsSingleton();

ModelsSingleton::ModelsSingleton(void)
{
	_modelsCount = 0;
	
	_models.clear();
	
	_modelCube.InitModel( ".\\Resources\\cube.obj" , ".\\Resources\\diamond_ore.png" );

	_modelTorus.InitModel( ".\\Resources\\torus.obj" , ".\\Resources\\stonebrick_mossy.png" );

	_modelThing.InitModel( ".\\Resources\\untitled.obj" , ".\\Resources\\redstone_block.png" );

	_modelBook.InitModel( ".\\Resources\\LivreFerme.obj" , ".\\Resources\\LivreFermeRouge.png" );
	

	Model* m1 = Instanciate(Cube, Point3(0.0f, 1.0f, -1.0f), Point3(0.0f, 0.0f, 0.0f));
	m1->AddComponent(new ColliderComponent(m1));
	m1->AddComponent(new PlayerScript(m1));

	Model* m2 = Instanciate(Torus);
	m2->SetTexture(".\\Resources\\stonebrick_mossy.png");
	m2->AddComponent(new TestScript(m2));

}


ModelsSingleton::~ModelsSingleton(void)
{
	std::list<Model*>::iterator it = _models.begin();
	while (it != _models.end())
	{
		delete (*it);
		it = _models.erase(it);
	}
}

ModelsSingleton& ModelsSingleton::Instance()
{
	return _instance;
}

Model* ModelsSingleton::Instanciate(ModelName modelName)
{
	Model* model;

	switch(modelName)
	{

	case Torus:
		model = new Model(_modelTorus);
		break;

	case Book:
		model = new Model(_modelBook);
		break;

	case Thing:
		model = new Model(_modelThing);
		break;

	case Cube:
	default:
		model = new Model(_modelCube);
		break;

	}

	if( model == NULL )
		return NULL;

	_models.push_back(model);

	_modelsCount++;

	return model;

}

Model* ModelsSingleton::Instanciate(ModelName modelName, Point3 position, Point3 rotation)
{
	Model* model;

	switch(modelName)
	{

	case 1: //ModelName::Torus:
		model = new Model(_modelTorus);
		break;

	case 2: //ModelName::Book:
		model = new Model(_modelBook);
		break;

	case 3: //ModelName::Thing:
		model = new Model(_modelThing);
		break;

	case 0: //ModelName::Cube:
	default:
		model = new Model(_modelCube);
		break;

	}

	if( model == NULL )
		return NULL;

	model->SetLocation(position);
	model->SetRotation(rotation);

	_models.push_back(model);

	_modelsCount++;

	return model;
}
