#pragma once
#include "SceneManager.h"



class EngineManager
{
private:
	char message[1000];
	SceneManager* scene;
public:
	EngineManager();

	EngineManager(SceneManager* scene);

	void Game();

	void BoomCheck();

	void Work();

	void Print_Map();

	~EngineManager();
};