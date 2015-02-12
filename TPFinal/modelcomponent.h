#pragma once
#include "args.h"
#include <list>


struct Model;
struct Point3;

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


////////////////////////////////
//  COLLIDER COMPONENT CLASS  //
////////////////////////////////
class ColliderComponent : public ModelComponent
{

public:
	ColliderComponent(Model* model);
	~ColliderComponent(void);
	virtual void Action(UpdateArgs& args);

private:
	// coordinates of the AABB
	float xMin, yMin, zMin,
		  xMax, yMax, zMax;

	// coordinates of the AABB
	float collisionXMin, collisionYMin, collisionZMin,
		  collisionXMax, collisionYMax, collisionZMax;

	// register AABB for this frame
	void RegisterAABB();

	// check if AABB collide with AABB in parameter
	bool IsAABBColliding(const Model* model);

	// check if Models collide by face
	bool AreModelsColliding(Model* model);

	// check the collision of each face of one list with the other
	bool Tri2Tri_Intersect(Point3 pt11, Point3 pt12, Point3 pt13, Point3 pt21, Point3 pt22, Point3 pt23);
	bool Lin2Tri_Intersect(Point3 T1, Point3 T2, Point3 T3, Point3 L1, Point3 L2);
	bool ResolveSystem(const Point3 &a0, const Point3 &a1, const Point3 &a2, Point3 &x, const Point3 &b);
	float CalculateDeterminant(const Point3 &u, const Point3 &v, const Point3 &w);
};
