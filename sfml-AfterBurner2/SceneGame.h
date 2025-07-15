#pragma once
#include "Scene.h"
class Tomcat;
class SceneGame : public Scene
{
protected:
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

