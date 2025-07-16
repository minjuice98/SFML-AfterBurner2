#include "stdafx.h"
#include "SceneMgr.h"
#include "SceneTitle.h"

SceneTitle::SceneTitle(SceneIds id) : Scene(SceneIds::Title)
{
}

void SceneTitle::Init()
{
	fontIds.push_back("fonts/KOMIKAP_.ttf");

	titleMessage.setFont(FONT_MGR.Get("fonts/KOMIKAP_.ttf"));
	titleMessage.setPosition({ 200.f,300.f });
	titleMessage.setString("After Burner 2 Clone, Enter");

	Scene::Init();
}
void SceneTitle::Enter()
{
	Scene::Enter();
}
void SceneTitle::Update(float dt)
{
	Scene::Update(dt);
	
	if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneIds::Game);
	}
}

void SceneTitle::Draw(sf::RenderWindow& window)
{
	window.draw(titleMessage);
	Scene::Draw(window);
}