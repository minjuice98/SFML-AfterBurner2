#pragma once
#include "stdafx.h"
#include "GameObject.h"
class GameUI : public GameObject
{
protected:
	sf::Text scoreMessage;
	sf::Text HitMessage;
	sf::Text StageMesseage;

	sf::Sprite scoreIcon;
	sf::Sprite hitIcon;
	sf::Sprite speedIcon;
	sf::Sprite stageIcon;
public:
	GameUI(const std::string& name);
	virtual ~GameUI() = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};