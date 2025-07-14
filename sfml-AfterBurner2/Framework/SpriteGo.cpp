#include "stdafx.h"
#include "SpriteGo.h"

SpriteGo::SpriteGo(const std::string& texId, const std::string& name)
	:GameObject(name), textureId(texId)
{

}
void SpriteGo::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(pos);
}
void SpriteGo::SetRotation(float rot)
{
	rotation = rot;
	sprite.setRotation(rot);
}
void SpriteGo::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sprite.setScale(s);
}
void SpriteGo::SetOrigin(const sf::Vector2f& o)
{
	origin = o;
	sprite.setOrigin(origin);
}

void SpriteGo::Init()
{
}

void SpriteGo::Release()
{
}

void SpriteGo::Reset()
{
	//텍스쳐 sprite 적용
	sprite.setTexture(TEXTURE_MGR.Get(textureId));
}

void SpriteGo::Update(float dt)
{
}

void SpriteGo::Draw(sf::RenderWindow& window)
{
	if (active)
	{
		window.draw(sprite);
	}
}