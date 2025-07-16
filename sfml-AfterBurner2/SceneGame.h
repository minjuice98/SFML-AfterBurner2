#pragma once
#include "Scene.h"
class Background;
class Enemy;
class Tomcat;
class SceneGame : public Scene
{
protected:
	Background* background = nullptr;
	Enemy* enemy = nullptr;
	Tomcat* tomcat = nullptr;
public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};