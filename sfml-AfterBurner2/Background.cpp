#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& name) : GameObject(name)
{
}

void Background::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	background.setPosition(pos);
}
void Background::SetRotation(const float r)
{
	GameObject::SetRotation(r);
	background.setRotation(r);
}

void Background::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	background.setScale(s);
}

void Background::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	background.setOrigin(o);
}

void Background::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void Background::Release()
{
}

void Background::Reset()
{
	background.setTexture(TEXTURE_MGR.Get("graphics/background.png"), true);
	background.setOrigin(background.getTexture()->getSize().x*0.5f
			,background.getTexture()->getSize().y*0.5f);
	background.setPosition({ 0.f,0.f });
	background.setRotation(0.f);

	minX = 380.f;
	maxX = 580.f;
	minY = 236.f;
	maxY = 436.f;
}

void Background::Update(float dt)
{
	const float moveSpeed = 200.f;
	if (InputMgr::GetKey(sf::Keyboard::Left)) 
	{
		background.move(moveSpeed * dt, 0.f);
	}
	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		background.move(-moveSpeed * dt, 0.f);
	}
	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		background.move(0.f, -moveSpeed * dt);
	}
	if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		background.move(0.f, moveSpeed * dt);
	}

	sf::Vector2f pos = background.getPosition();
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	background.setPosition(pos);
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(background);
}