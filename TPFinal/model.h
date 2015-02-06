#pragma once

#include <iostream>
using namespace std;

#include "face.h"
#include <map>
#include <list>

struct Model
{

	Model(void);
	Model(const Model& model);
	~Model(void);
	bool InitModel( string modelName, string textureName );

	std::map<int, Face*> _faces;
	int nbFace;

	std::map<int, Point3> _vertex;
	int nbVertex;

	std::map<int, Point2> _textures;
	int nbTexture;

	string _name;
	
	// Texture
	void SetTexture(std::string newTex);
	string _texture;
	
	// Transformed Points
	void Update();
	std::map<int, Point3> _listVertex;

	// Location
	void SetLocation(Point3 newLoc);
	void SetLocation(float x, float y, float z);
	void Translate(Point3 newLoc);
	void Translate(float x, float y, float z);
	Point3 _location;
	Point3 _futureLocation;
	bool _changeLocation;

	// Rotation
	void SetRotation(Point3 axis, float angle);
	void SetRotation(float xAngle, float yAngle, float zAngle);
	void Rotate(Point3 axis, float angle);
	void Rotate(float xAngle, float yAngle, float zAngle);
	Point3 _rotation;
	bool _changeRotation;

	// Scale
	void SetScale(float scale);
	void Scale(float factor);
	float _scale;
	float _futureScale;
	bool _changeScale;

private :
	bool ReadFileCounts();
	bool LoadData();
	bool InitVertexList();

};

