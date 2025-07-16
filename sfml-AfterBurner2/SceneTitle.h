#pragma once
#include "Scene.h"
class SceneTitle : public Scene
{
protected:
	sf::Text titleMessage;
public:
	SceneTitle(SceneIds id);
	~SceneTitle() = default;

	void Init() override;
	void Enter() override;

	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};