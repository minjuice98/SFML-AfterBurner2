#include "stdafx.h"
#include "SceneGame.h"
#include "Tomcat.h"

SceneGame::SceneGame(SceneIds id) : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/tomcat.png");
	TEXTURE_MGR.Load(texIds);
	tomcat = (Tomcat*)AddGameObject(new Tomcat("Tomcat"));
	
	Scene::Init();
}

void SceneGame::Enter()
{
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
