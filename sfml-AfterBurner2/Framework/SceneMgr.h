#pragma once
#include "stdafx.h"

class SceneMgr :public Singleton<SceneMgr>
{
	friend class Singleton<SceneMgr>; //singleton<SceneMgr> 클래스(자식 클래스 x)가 SceneMgr protected 생성자 호출

protected:
	SceneMgr() = default;
	~SceneMgr() = default;

	std::vector<Scene*> scenes;

	SceneIds startScene = SceneIds::Title;
	SceneIds currentScene = SceneIds::None;
	SceneIds nextScene = SceneIds::None;

public:
	void Init();
	void Release();

	Scene* GetCurrentScene() { return scenes[(int)currentScene]; }
	SceneIds GetCurrentSceneId() const { return currentScene; } //수정금지
	void ChangeScene(SceneIds id);

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
};
#define SCENE_MGR (SceneMgr::Instance())