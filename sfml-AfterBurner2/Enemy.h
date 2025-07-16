#pragma once
#include "GameObject.h"
class Enemy :  public GameObject
{
protected:
	sf::Sprite enemy;
	std::string texId;
	std::string name;

	sf::Vector2f velocity; 

public:
	Enemy(const std::string& name = "");
	~Enemy() override = default;

	sf::Vector2f GetPosition() const { return position; }
	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(const float r) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};