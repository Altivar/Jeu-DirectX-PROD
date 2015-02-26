#include "guimanager.h"
#include "gamemanager.h"
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
	_isPaused = false;
	
	// click gesture
	Click_F1 = false;
	Click_ESC = false;
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
	
	// F1 button gesture
	if(GetAsyncKeyState(VK_F1))
	{
		if( !Click_F1 )
			_inGameInfoEnable = !_inGameInfoEnable;
		Click_F1 = true;
	}
	else
		Click_F1 = false;

	// Escape button gesture
	if(GetAsyncKeyState(VK_ESCAPE))
	{
		if( !Click_ESC )
		{
			GameManager::Instance()->Pause();
			_isPaused = !_isPaused;
		}
		Click_ESC = true;
	}
	else
		Click_ESC = false;


	return _sceneState;
}