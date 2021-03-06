#pragma once

#include <string>

class GUIManager
{
public:
	static GUIManager* Instance();
	static void ReleaseInstance();

	int CheckForSceneState();
	bool IsGameInfoEnable() { return _inGameInfoEnable; }
	bool IsGamePaused() { return _isPaused; }
	void PlayerCollided(std::string file);
	std::string GetFatalBallImage() { return _ballFile; }

private:
	GUIManager(void);
	~GUIManager(void);

	static GUIManager* _instance;

	int _sceneState;
	bool _inGameInfoEnable;
	bool _isPaused;
	std::string _ballFile;

	bool Click_F1;
	bool Click_ESC;
	bool Click_RET;

};

