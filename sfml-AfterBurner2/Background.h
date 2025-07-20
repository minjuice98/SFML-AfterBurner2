#pragma once
#include "GameObject.h"
class Background : public GameObject
{
protected:
	sf::Sprite stage1first;
	sf::Sprite stage1second;
	sf::RectangleShape sky;

	std::string texId;
	std::string name;

	float scrollSpeed = 400.f;
	float moveSpeed = 300.f;

	float minX = 0.f;
	float maxX = 0.f;
	float backgroundHeight;
public:
	Background(const std::string& name="");
	~Background() override=default;

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