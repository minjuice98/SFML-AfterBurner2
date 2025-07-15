#include "stdafx.h"
#include "SceneMgr.h"

void SceneMgr::Init()
{
	//scenes.push_back(); //vector 컨테이너

	for (auto scene : scenes)
	{
		scene->Init();
	}
	currentScene = startScene;
	scenes[(int)currentScene]->Enter(); //해당 scene resource load
}

void SceneMgr::Release()
{
	for (auto scene : scenes)
	{
		if (scene->Id == currentScene)
		{
			scene->Exit();
		}
		scene->Release();
		delete scene;
	}
	scenes.clear();
}

void SceneMgr::ChangeSceen(SceneIds id)
{
	nextScene = id;
}

void SceneMgr::Update(float dt)
{
	if (nextScene != SceneIds::None)
	{
		scenes[(int)currentScene]->Exit();
		currentScene = nextScene;
		nextScene = SceneIds::None;
		scenes[(int)currentScene]->Enter();
	}
	scenes[(int)currentScene]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentScene]->Draw(window);
}