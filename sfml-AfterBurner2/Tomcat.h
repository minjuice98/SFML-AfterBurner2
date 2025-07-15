#pragma once
#include "GameObject.h"
class Tomcat :public GameObject
{
protected:
	sf::Sprite tomcat;
	std::string texId = "graphics/tomcat.png";

	float minX;
	float maxX;
	float minY;
	float maxY;
public:
	Tomcat(const std::string& name="");
	~Tomcat() override = default;

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};