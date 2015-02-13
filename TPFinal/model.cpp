#include "Model.h"
#include "eventmanager.h"
#include <fstream>
#include <sstream>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG

float PI = 3.141592f;

Model::Model(void)
{
	SetLocation(0,0,0);
	_futureLocation = _location;
	SetRotation(0,0,0);
	SetScale(1);
	_scale = 1.0f;
	_changeLocation = false;
	_changeRotation = false;
	_changeScale = false;
	_listVertex.clear();
	_components.clear();
	_modelNum = -1;
	_hasBeenInitialized = false;
}

Model::Model(const Model& model)
{
	this->nbFace = 0;
	std::map<int, Face*>::const_iterator it1 = model._faces.begin();
	for( it1; it1 != model._faces.end(); it1++ )
	{
		Face* newFace = new Face();
		for(int i = 0; i < (*it1).second->_nbVertex; i++)
		{
			newFace->AddVertex((*it1).second->_vertexTable[i]);
		}
		this->_faces[it1->first] = newFace;
		this->nbFace++;
	}
	
	this->nbVertex = 0;
	std::map<int, Point3>::const_iterator it2 = model._vertex.begin();
	for( it2; it2 != model._vertex.end(); it2++ )
	{
		this->_vertex[it2->first] = it2->second;
		this->nbVertex++;
	}
	
	this->nbTexture = 0;
	std::map<int, Point2>::const_iterator it3 = model._textures.begin();
	for( it3; it3 != model._textures.end(); it3++ )
	{
		this->_textures[it3->first] = it3->second;
		this->nbTexture++;
	}

	this->_listVertex.clear();
	this->_listVertex = model._listVertex;

	this->_components.clear();

	this->_texture = model._texture;
	this->_name = model._name;
	
	this->_location = model._location;
	_futureLocation = _location;
	this->_rotation = model._rotation;
	this->_scale = model._scale;
	_futureScale = _scale;

	_changeLocation = false;
	_changeRotation = false;
	_changeScale = false;

	_modelNum = -1;
	_hasBeenInitialized = false;
}

Model::~Model(void)
{
	std::map<int, Face*>::iterator it = _faces.begin();
	while (it != _faces.end())
	{
		delete (*it).second;
		it = _faces.erase(it);
	}

	std::list<ModelComponent*>::iterator it2 = _components.begin();
	while (it2 != _components.end())
	{
		delete (*it2);
		it2 = _components.erase(it2);
	}
}

///////////
//  INIT //
///////////
bool Model::InitModel( string modelName, string textureName )
{

	// init the path the object
	_name = modelName;

	// init the model
	bool result;
	
	result = ReadFileCounts();
	if( !result )
	{
		MessageBox(NULL, "Error when trying to read the file !",  "Game", MB_OK);
		return false;
	}

	result = LoadData();
	if( !result )
	{
		MessageBox(NULL, "Error when trying to read the file !",  "Game", MB_OK);
		return false;
	}

	result = InitVertexList();
	if( !result )
	{
		MessageBox(NULL, "Error while initializing the model !",  "Game", MB_OK);
		return false;
	}

	// init the texture
	_texture = textureName;

	return true;
}

////////////////
//  LOCATION  //
////////////////
void Model::SetLocation(Point3 newLoc)
{
	_futureLocation.x = newLoc.x;
	_futureLocation.y = newLoc.y;
	_futureLocation.z = newLoc.z;

	_changeLocation = true;
}

void Model::SetLocation(float x, float y, float z)
{
	_futureLocation.x = x;
	_futureLocation.y = y;
	_futureLocation.z = z;

	_changeLocation = true;
}

void Model::Translate(Point3 newLoc)
{
	_futureLocation.x += newLoc.x;
	_futureLocation.y += newLoc.y;
	_futureLocation.z += newLoc.z;

	_changeLocation = true;
}

void Model::Translate(float x, float y, float z)
{
	_futureLocation.x += x;
	_futureLocation.y += y;
	_futureLocation.z += z;

	_changeLocation = true;
}

////////////////
//  ROTATION  //
////////////////
void Model::SetRotation(Point3 rotation)
{
	this->_rotation.x = rotation.x;
	this->_rotation.y = rotation.y;
	this->_rotation.z = rotation.z;

	_changeRotation = true;
}

void Model::SetRotation(Point3 axis, float angle)
{
	this->_rotation.x = axis.x * angle;
	this->_rotation.y = axis.y * angle;
	this->_rotation.z = axis.z * angle;

	_changeRotation = true;
}

void Model::SetRotation(float xAngle, float yAngle, float zAngle)
{
	this->_rotation.x = xAngle;
	this->_rotation.y = yAngle;
	this->_rotation.z = zAngle;

	_changeRotation = true;
}

void Model::Rotate(Point3 axis, float angle)
{
	this->_rotation.x += axis.x * angle;
	this->_rotation.y += axis.y * angle;
	this->_rotation.z += axis.z * angle;

	_changeRotation = true;
}

void Model::Rotate(float xAngle, float yAngle, float zAngle)
{
	this->_rotation.x += xAngle;
	this->_rotation.y += yAngle;
	this->_rotation.z += zAngle;

	_changeRotation = true;
}

/////////////
//  SCALE  //
/////////////
void Model::SetScale(float scale)
{
	this->_futureScale = scale;

	_changeScale = true;
}

void Model::Scale(float factor)
{
	this->_futureScale *= factor;

	_changeScale = true;
}

///////////////
//  TEXTURE  //
///////////////
void Model::SetTexture(std::string newTex)
{
	_texture = newTex;
}

//////////////
//  UPDATE  //
//////////////
void Model::Update()
{
	
	if(_changeRotation)
	{
		_listVertex.clear();

		for(int i = 1; i <= this->nbVertex; i++)
		{
			Point3 vertex = _vertex[i];
				
			float x, y, z;

			// rotate x
			float cos_X = cos( _rotation.x );
			float sin_X = sin( _rotation.x );
			y = vertex.y;
			z = vertex.z;
			vertex.y = y * cos_X - z * sin_X;
			vertex.z = z * cos_X + y * sin_X;

			// rotate y
			float cos_Y = cos( _rotation.y );
			float sin_Y = sin( _rotation.y );
			x = vertex.x;
			z = vertex.z;
			vertex.z = z * cos_Y - x * sin_Y;
			vertex.x = x * cos_Y + z * sin_Y;

			// rotate z
			float cos_Z = cos( _rotation.z );
			float sin_Z = sin( _rotation.z );
			x = vertex.x;
			y = vertex.y;
			vertex.x = x * cos_Z - y * sin_Z;
			vertex.y = y * cos_Z + x * sin_Z;

			// scale
			vertex.x *= _scale;
			vertex.y *= _scale;
			vertex.z *= _scale;

			// position
			vertex.x += _futureLocation.x;
			vertex.y += _futureLocation.y;
			vertex.z += _futureLocation.z;

			_listVertex[i] = vertex;
		}
	}
	else if (_changeScale)
	{

		float diffScale = _futureScale;
		if( _scale == 0 )
			diffScale /= 0.0001f;
		else
			diffScale /= _scale;

		for(int i = 1; i <= this->nbVertex; i++)
		{
			// position
			_listVertex[i].x -= _location.x;
			_listVertex[i].y -= _location.y;
			_listVertex[i].z -= _location.z;

			// scale
			_listVertex[i].x *= diffScale;
			_listVertex[i].y *= diffScale;
			_listVertex[i].z *= diffScale;

			// position
			_listVertex[i].x += _futureLocation.x;
			_listVertex[i].y += _futureLocation.y;
			_listVertex[i].z += _futureLocation.z;
		}
	}
	else if(_changeLocation)
	{
		Point3 diffLocation = _futureLocation;
		diffLocation.x -= _location.x;
		diffLocation.y -= _location.y;
		diffLocation.z -= _location.z;

		for(int i = 1; i <= this->nbVertex; i++)
		{
			// position
			_listVertex[i].x += diffLocation.x;
			_listVertex[i].y += diffLocation.y;
			_listVertex[i].z += diffLocation.z;
		}
	}

	_location = _futureLocation;
	_scale = _futureScale;
	_changeLocation = false;
	_changeRotation = false;
	_changeScale = false;

}

//////////////////
//  COMPONENTS  //
//////////////////
void Model::AddComponent(ModelComponent* component)
{
	if( component == NULL )
		return;

	// if the new component is a script
	// attach it to the event manager (for the collision)
	if( ScriptComponent* script = dynamic_cast<ScriptComponent*>(component) )
	{

		std::stringstream ss;
		ss << "__COLLISION__" << this->_modelNum;
		std::string eventname = ss.str();

		EventManager::Instance().RegisterEvent( eventname , std::bind(&ScriptComponent::Collide, script, std::placeholders::_1));
	}


	_components.push_back(component);
}

//////////////////
//  LOAD MODEL  //
//////////////////
bool Model::ReadFileCounts()
{
	
	ifstream fin;
    char input;

    // Initialise les compteurs.
    nbVertex = 0;
    nbTexture = 0;
    nbFace = 0;

    // Ouvre le fichier.
    fin.open(_name);

    // Vérifie si le fichier a bien été ouvert.
    if(fin.fail())
    {
		fin.close();
        return false;
    }

    // Effectue la lecture du fichier jusqu'à atteindre la fin.
    fin.get(input);
    while(!fin.eof())
    {
        // Si la ligne commence par 'v', compte soit les sommets, 
    // soit les coordonnées de texture, soit les normales.
        if(input == 'v')
        {
            fin.get(input);
            if(input == ' ') { nbVertex++; }
            if(input == 't') { nbTexture++; }
        }

        // Si la ligne commence par 'f', incrémente le nombre de faces.
        if(input == 'f')
        {
            fin.get(input);
            if(input == ' ') { nbFace++; }
        }
        
        // Sinon, lit le reste de la ligne.
        while(input != '\n')
        {
            fin.get(input);
        }

        // Commence à lire le début de la ligne suivante.
        fin.get(input);
    }

    // Close the file.
    fin.close();

	return true;
}

bool Model::LoadData()
{
	ifstream fin;
    char input;

    // Ouvre le fichier.
    fin.open(_name);

    // Vérifie si le fichier a bien été ouvert.
    if(fin.fail())
    {
		fin.close();
        return false;
    }

	int indexVertex = 1;
	int indexTexture = 1;
	int indexFace = 1;

	fin.get(input);
    while(!fin.eof())
    {
        if(input == 'v')
        {
            fin.get(input);

            // Lit les sommets.
            if(input == ' ') 
            { 
                float x, y, z;
				fin >> x >> y >> z;

				Point3 pt3;
				pt3.x = x;
				pt3.y = y;
				pt3.z = z;

				_vertex[indexVertex] = pt3;
				indexVertex++;
            }

            // Lit les coordonnées UV de texture.
            if(input == 't') 
            { 
				float x, y;
				fin >> x >> y;

				Point2 pt2;
				pt2.x = 1 - x;
				pt2.y = 1 - y;

				_textures[indexTexture] = pt2;
				indexTexture++;
            }

        }

        // Lit les faces.
        if(input == 'f') 
        {
            fin.get(input);
            if(input == ' ')
            {
				
				// create the face
				Face* face = new Face();
				// check and create all the vertex of the face
				while(true)
				{
					
					/*int v, t;
					fin >> v;
					fin.get(input);
					if(input == ' ' || input == '\n')
					{
						CUSTOM_VERTEX vertex;
						vertex.x = _vertex[v].x;
						vertex.y = _vertex[v].y;
						vertex.z = -_vertex[v].z;
						vertex.COLOR = 0xff80ff80;
						vertex.u = 0;
						vertex.v = 0;
						face->AddVertex(vertex);
					}
					else if (input == '/')
					{
						fin.get(input);
						t = atoi(&input);

						CUSTOM_VERTEX vertex;
						vertex.x = _vertex[v].x;
						vertex.y = _vertex[v].y;
						vertex.z = -_vertex[v].z;
						vertex.COLOR = 0xffff00ff;
						vertex.u = 1 - _textures[t].x;
						vertex.v = 1 - _textures[t].y;
						face->AddVertex(vertex);
					}
					else
						continue;


					while(input != ' ' && input != '\n')
						fin.get(input);
					if(input == '\n')
						break;*/
					///////////////////////////////////////////////////////

					///////////////////////////////////////////////////////
					int v, t;
					fin >> v >> input >> t;

					CUSTOM_VERTEX_DATA vertex;
					vertex.vertexPosition = v;
					vertex.COLOR = 0xffff00ff;
					vertex.texturePosition = t;
					face->AddVertex(vertex);

					while(input != ' ' && input != '\n')
						fin.get(input);
					if(input == '\n')
						break;
				}

				if(face->_nbVertex == 0)
				{
					delete face;
				}

				_faces[indexFace] = face;
				indexFace++;
            }
        }

        // Lit le reste de la ligne.
        while(input != '\n')
        {
            fin.get(input);
        }

        // Commence à lire la ligne suivante.
        fin.get(input);
    }

	fin.close();

	return true;

}

bool Model::InitVertexList()
{
	for(int i = 1; i <= this->nbVertex; i++)
	{
		_listVertex[i] = _vertex[i];
	}
	return true;
}