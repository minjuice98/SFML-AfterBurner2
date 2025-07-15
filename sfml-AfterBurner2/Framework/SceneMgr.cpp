#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneTitle.h"
#include "SceneGame.h"

void SceneMgr::Init()
{
	scenes.push_back(new SceneTitle(SceneIds::Title)); //vector 컨테이너
	scenes.push_back(new SceneGame(SceneIds::Game)); //vector 컨테이너

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

void SceneMgr::ChangeScene(SceneIds id)
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