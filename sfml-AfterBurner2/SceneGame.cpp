#include "stdafx.h"
#include "SceneGame.h"
#include "Background.h"
#include "Enemy.h"
#include "Tomcat.h"

SceneGame::SceneGame(SceneIds id) : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/background.png");
	texIds.push_back("graphics/enemy.png");
	texIds.push_back("graphics/tomcat.png");
	texIds.push_back("graphics/crosshair.png");
	TEXTURE_MGR.Load(texIds);
	
	background = (Background*)AddGameObject(new Background("Background"));
	enemy = (Enemy*)AddGameObject(new Enemy("Enemy"));
	tomcat = (Tomcat*)AddGameObject(new Tomcat("Tomcat"));
	
	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	worldView.setSize(windowSize);
	worldView.setCenter({ 0.f,0.f });
	
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	worldView.setCenter(tomcat->GetPosition());
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
