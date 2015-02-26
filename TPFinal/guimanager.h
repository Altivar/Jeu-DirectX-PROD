#pragma once
class GUIManager
{
public:
	static GUIManager* Instance();
	static void ReleaseInstance();

	int CheckForSceneState();
	int IsGameInfoEnable() { return _inGameInfoEnable; }

private:
	GUIManager(void);
	~GUIManager(void);

	static GUIManager* _instance;

	int _sceneState;
	bool _inGameInfoEnable;

	bool Click_F1;

};

