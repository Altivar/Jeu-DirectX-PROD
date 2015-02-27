#include "modelcomponent.h"
#include "model.h"
#include "modelssingleton.h"
#include <sstream>

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

// called at each frame
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

void ScriptComponent::Collide(EventArgs args)
{
}



////////////////////////////////
//  COLLIDER COMPONENT CLASS  //
////////////////////////////////
ColliderComponent::ColliderComponent(Model* model)
	: ModelComponent(model)
{
	xMin = 0;
	xMax = 0;
	yMin = 0;
	yMax = 0;
	zMin = 0;
	zMax = 0;

	collisionYMin = 0;
	collisionYMax = 0;
	collisionYMin = 0;
	collisionYMax = 0;
	collisionZMin = 0;
	collisionZMax = 0;
}

ColliderComponent::~ColliderComponent(void)
{
}

// called at each frame
void ColliderComponent::Action(UpdateArgs& args)
{
	
	RegisterAABB();

	std::list<Model*>::iterator modelIt = ModelsSingleton::Instance()->_models.begin();
	for( modelIt; modelIt != ModelsSingleton::Instance()->_models.end(); modelIt++ )
	{
		if( (*modelIt) == _baseModel )
			continue;

		if( !(*modelIt)->_hasBeenInitialized )
			continue;

		if( IsAABBColliding(*modelIt) )
		{
			if( AreModelsColliding(*modelIt) )
			{
				std::stringstream ss;
				ss << "__COLLISION__" << _baseModel->_modelNum;
				std::string eventname = ss.str();

				std::string tex = (*modelIt)->_texture;
				tex.erase(tex.end()-4, tex.end());
				std::stringstream ss2;
				ss2 << tex << "Image.png";
				
				EventArgs arg;
				arg.strArgs = ss2.str();

				EventManager::Instance()->FireEvent(eventname, arg);
			}
		}
	}


}

// register AABB for this frame
void ColliderComponent::RegisterAABB()
{
	std::map<int, Point3>::iterator vertexIt = _baseModel->_listVertex.begin();
	
	// stack the first vertex has AABB
	xMin = (*vertexIt).second.x;
	xMax = (*vertexIt).second.x;
	yMin = (*vertexIt).second.y;
	yMax = (*vertexIt).second.y;
	zMin = (*vertexIt).second.z;
	zMax = (*vertexIt).second.z;
	vertexIt++;

	for( vertexIt; vertexIt != _baseModel->_listVertex.end(); vertexIt++)
	{
		if( (*vertexIt).second.x < xMin )
			xMin = (*vertexIt).second.x;
		if( (*vertexIt).second.x > xMax )
			xMax = (*vertexIt).second.x;

		if( (*vertexIt).second.y < yMin )
			yMin = (*vertexIt).second.y;
		if( (*vertexIt).second.y > yMax )
			yMax = (*vertexIt).second.y;

		if( (*vertexIt).second.z < zMin )
			zMin = (*vertexIt).second.z;
		if( (*vertexIt).second.z > zMax )
			zMax = (*vertexIt).second.z;
	}
}

// check if AABB collide with AABB in parameter
bool ColliderComponent::IsAABBColliding(const Model* model)
{

	std::map<int, Point3>::const_iterator vertexIt = model->_listVertex.begin();
	
	// stack the first vertex has AABB
	float xmin = (*vertexIt).second.x;
	float xmax = (*vertexIt).second.x;
	float ymin = (*vertexIt).second.y;
	float ymax = (*vertexIt).second.y;
	float zmin = (*vertexIt).second.z;
	float zmax = (*vertexIt).second.z;
	vertexIt++;

	for( vertexIt; vertexIt != model->_listVertex.end(); vertexIt++)
	{
		if( (*vertexIt).second.x < xmin )
			xmin = (*vertexIt).second.x;
		if( (*vertexIt).second.x > xmax )
			xmax = (*vertexIt).second.x;

		if( (*vertexIt).second.y < ymin )
			ymin = (*vertexIt).second.y;
		if( (*vertexIt).second.y > ymax )
			ymax = (*vertexIt).second.y;

		if( (*vertexIt).second.z < zmin )
			zmin = (*vertexIt).second.z;
		if( (*vertexIt).second.z > zmax )
			zmax = (*vertexIt).second.z;
	}

	if( xmin > xMax )
		return false;
	if( xmax < xMin )
		return false;
	if( ymin > yMax )
		return false;
	if( ymax < yMin )
		return false;
	if( zmin > zMax )
		return false;
	if( zmax < zMin )
		return false;

	collisionXMax = (xmax < xMax) ? xmax : xMax;
	collisionXMin = (xmin > xMin) ? xmin : xMin;
	collisionYMax = (ymax < yMax) ? ymax : yMax;
	collisionYMin = (ymin > yMin) ? ymin : yMin;
	collisionZMax = (zmax < zMax) ? zmax : zMax;
	collisionZMin = (zmin > zMin) ? zmin : zMin;

	return true;
}

// check if Models collide by triangle
bool ColliderComponent::AreModelsColliding(Model* model)
{
	// lists of faces wich can collide with the other model
	std::list<int> _listFaceModel1;
	std::list<int> _listFaceModel2;
	_listFaceModel1.clear();
	_listFaceModel2.clear();

	int vertexPos = _baseModel->_faces[1]->_vertexTable[0].vertexPosition;
	Point3 ptMin;(_baseModel->_listVertex[vertexPos].x, _baseModel->_listVertex[vertexPos].y, _baseModel->_listVertex[vertexPos].z);
	Point3 ptMax;(_baseModel->_listVertex[vertexPos].x, _baseModel->_listVertex[vertexPos].y, _baseModel->_listVertex[vertexPos].z);

	// get all the face of the base model wich can collide with the other model
	for(int f = 1 ; f <= _baseModel->nbFace; f++)
	{
		vertexPos = _baseModel->_faces[f]->_vertexTable[0].vertexPosition;
		ptMin = Point3(model->_listVertex[vertexPos].x, model->_listVertex[vertexPos].y, model->_listVertex[vertexPos].z);
		ptMax = Point3(model->_listVertex[vertexPos].x, model->_listVertex[vertexPos].y, model->_listVertex[vertexPos].z);

		for( int i = 1; i < _baseModel->_faces[f]->_nbVertex; i++)
		{
			vertexPos = _baseModel->_faces[f]->_vertexTable[i].vertexPosition;

			if( ptMin.x > _baseModel->_listVertex[vertexPos].x )
				ptMin.x = _baseModel->_listVertex[vertexPos].x;
			if( ptMax.x < _baseModel->_listVertex[vertexPos].x )
				ptMax.x = _baseModel->_listVertex[vertexPos].x;

			if( ptMin.y > _baseModel->_listVertex[vertexPos].y )
				ptMin.y = _baseModel->_listVertex[vertexPos].y;
			if( ptMax.y < _baseModel->_listVertex[vertexPos].y )
				ptMax.y = _baseModel->_listVertex[vertexPos].y;

			if( ptMin.z > _baseModel->_listVertex[vertexPos].z )
				ptMin.z = _baseModel->_listVertex[vertexPos].z;
			if( ptMax.z < _baseModel->_listVertex[vertexPos].z )
				ptMax.z = _baseModel->_listVertex[vertexPos].z;
		}

		if( collisionXMin > ptMax.x )
			continue;
		if( collisionXMax < ptMin.x )
			continue;

		if( collisionYMin > ptMax.y )
			continue;
		if( collisionYMax < ptMin.y )
			continue;

		if( collisionZMin > ptMax.z )
			continue;
		if( collisionZMax < ptMin.z )
			continue;

		_listFaceModel1.push_back(f);
	}
	
	
	// get all the face of the base model wich can collide with the other model
	for(int f = 1 ; f <= model->nbFace; f++)
	{
		vertexPos = model->_faces[f]->_vertexTable[0].vertexPosition;
		ptMin = Point3(model->_listVertex[vertexPos].x, model->_listVertex[vertexPos].y, model->_listVertex[vertexPos].z);
		ptMax = Point3(model->_listVertex[vertexPos].x, model->_listVertex[vertexPos].y, model->_listVertex[vertexPos].z);

		for( int i = 1; i < model->_faces[f]->_nbVertex; i++)
		{
			vertexPos = model->_faces[f]->_vertexTable[i].vertexPosition;

			if( ptMin.x > model->_listVertex[vertexPos].x )
				ptMin.x = model->_listVertex[vertexPos].x;
			if( ptMax.x < model->_listVertex[vertexPos].x )
				ptMax.x = model->_listVertex[vertexPos].x;

			if( ptMin.y > model->_listVertex[vertexPos].y )
				ptMin.y = model->_listVertex[vertexPos].y;
			if( ptMax.y < model->_listVertex[vertexPos].y )
				ptMax.y = model->_listVertex[vertexPos].y;

			if( ptMin.z > model->_listVertex[vertexPos].z )
				ptMin.z = model->_listVertex[vertexPos].z;
			if( ptMax.z < model->_listVertex[vertexPos].z )
				ptMax.z = model->_listVertex[vertexPos].z;
		}

		if( collisionXMin > ptMax.x )
			continue;
		if( collisionXMax < ptMin.x )
			continue;

		if( collisionYMin > ptMax.y )
			continue;
		if( collisionYMax < ptMin.y )
			continue;

		if( collisionZMin > ptMax.z )
			continue;
		if( collisionZMax < ptMin.z )
			continue;

		_listFaceModel2.push_back(f);
	}

	// if in one model, there is no face near the collision box return false
	if(_listFaceModel1.empty())
		return false;
	if(_listFaceModel2.empty())
		return false;


	std::list<int>::iterator it1 = _listFaceModel1.begin();
	std::list<int>::iterator it2 = _listFaceModel2.begin();

	for( it1; it1 != _listFaceModel1.end(); it1++ )
	{
		for( it2; it2 != _listFaceModel2.end(); it2++ )
		{
			
			for(int i = 1; i < _baseModel->_faces[(*it1)]->_nbVertex - 1; i++)
			{
				for(int j = 1; j < model->_faces[(*it2)]->_nbVertex - 1; j++)
				{
					Point3 pt11 = _baseModel->_listVertex[_baseModel->_faces[(*it1)]->_vertexTable[0].vertexPosition];
					Point3 pt12 = _baseModel->_listVertex[_baseModel->_faces[(*it1)]->_vertexTable[i].vertexPosition];
					Point3 pt13 = _baseModel->_listVertex[_baseModel->_faces[(*it1)]->_vertexTable[i+1].vertexPosition];
					Point3 pt21 = model->_listVertex[model->_faces[(*it2)]->_vertexTable[0].vertexPosition];
					Point3 pt22 = model->_listVertex[model->_faces[(*it2)]->_vertexTable[j].vertexPosition];
					Point3 pt23 = model->_listVertex[model->_faces[(*it2)]->_vertexTable[j+1].vertexPosition];

					if( Tri2Tri_Intersect(pt11, pt12, pt13, pt21, pt22, pt23) )
						return true;
				}
			}

		}
	}

	return false;
}

// check the collision of each face of one list with the other
bool ColliderComponent::Tri2Tri_Intersect(Point3 pt11, Point3 pt12, Point3 pt13, Point3 pt21, Point3 pt22, Point3 pt23)
{
	
	if( Lin2Tri_Intersect(pt11, pt12, pt13, pt21, pt22) )
		return true;
	if( Lin2Tri_Intersect(pt11, pt12, pt13, pt22, pt23) )
		return true;
	if( Lin2Tri_Intersect(pt11, pt12, pt13, pt21, pt23) )
		return true;

	if( Lin2Tri_Intersect(pt21, pt22, pt23, pt11, pt12) )
		return true;
	if( Lin2Tri_Intersect(pt21, pt22, pt23, pt12, pt13) )
		return true;
	if( Lin2Tri_Intersect(pt21, pt22, pt23, pt11, pt13) )
		return true;

	return false;

}

bool ColliderComponent::Lin2Tri_Intersect(Point3 T0, Point3 T1, Point3 T2, Point3 L1, Point3 L2)
{
	
	Point3 AOr1 = L2 - T0;
	Point3 AOr2 = L1 - T0;
	Point3 AB = T1 - T0;
	Point3 AC = T2 - T0;

	Point3 mDr1 = L1 - L2;
	mDr1.Normalize();
	Point3 mDr2 = L2 - L1;
	mDr2.Normalize();

	Point3 vI1;
	if (!ResolveSystem(AB, AC, mDr1, vI1, AOr1))
		return false;
	//if (vI1.z<=0 || vI1.x<0 || vI1.x>1 || vI1.y<0 || vI1.y>1 || (vI1.x+vI1.y)>1)
	//	return false;

	Point3 vI2;
	if (!ResolveSystem(AB, AC, mDr2, vI2, AOr2))
		return false;
	//if (vI2.z<=0 || vI2.x<0 || vI2.x>1 || vI2.y<0 || vI2.y>1 || (vI2.x+vI2.y)>1)
	//	return false;/**/

	return true;

}

bool ColliderComponent::ResolveSystem(const Point3 &a0, const Point3 &a1, const Point3 &a2, Point3 &x, const Point3 &b)
{
	const float EPSILON = 1e-6f;

	// applique la methode de Cramer (pas efficace mais assez robuste)
	float d = CalculateDeterminant(a0, a1, a2);
	if (fabs(d)<EPSILON)
		return false;
	x.x = CalculateDeterminant(b, a1, a2);
	x.y = CalculateDeterminant(a0, b, a2);
	x.z = CalculateDeterminant(a0, a1, b);
	x *= 1/d;
	return true;
}

float ColliderComponent::CalculateDeterminant(const Point3 &u, const Point3 &v, const Point3 &w)
{
	return u.x*v.y*w.z + v.x*w.y*u.z + w.x*u.y*v.z
			- w.x*v.y*u.z - u.x*w.y*v.z - v.x*u.y*w.z;
}
