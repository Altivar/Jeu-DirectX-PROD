#include "guimanager.h"
#include <iostream>
#include <Windows.h>

// memory leaks
#include <crtdbg.h>
#ifdef _DEBUG 
  #define new new( _CLIENT_BLOCK, __FILE__, __LINE__)
#endif // _DEBUG 

GUIManager* GUIManager::_instance = NULL;

GUIManager::GUIManager(void)
{
	_sceneState = 0;
	_inGameInfoEnable = false;
	
	// click gesture
	Click_F1 = false;
}

GUIManager::~GUIManager(void)
{
}

//////////////////////////
//  SINGLETON INSTANCE  //
//////////////////////////
GUIManager* GUIManager::Instance()
{
	if( _instance == NULL )
		_instance = new GUIManager();
	return _instance;
}

void GUIManager::ReleaseInstance()
{
	delete _instance;
	_instance = NULL;
}

/////////////////////////////
//  GUI MANAGER FUNCTIONS  //
/////////////////////////////
int GUIManager::CheckForSceneState()
{
	
	if(GetAsyncKeyState(VK_F1))
	{
		if( !Click_F1 )
			_inGameInfoEnable = !_inGameInfoEnable;
		Click_F1 = true;
	}
	else
		Click_F1 = false;



	return _sceneState;
}