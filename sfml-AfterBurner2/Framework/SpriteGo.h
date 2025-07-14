#pragma once
#include "stdafx.h"
#include "GameObject.h"

/* Sprite
* 1. texture 로딩
* 2. position, rotation, scale, origin 설정
* 3. reset() 에서 매핑
*/

class SpriteGo : public GameObject
{
protected:
	sf::Sprite sprite;
	std::string textureId;
public:
	SpriteGo(const std::string& texId = "", const std::string& name = "");
	~SpriteGo() override = default;

	const std::string& GetTextureId() const { return textureId; }
	void SetTextureId(const std::string& texId) { textureId = texId; }

	sf::Sprite& GetSprite() { return sprite; }
	const sf::Sprite& GetSprite() const { return sprite; }

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;

	// GameObject을(를) 통해 상속됨
	void Init() override;

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;
};