#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& name) : GameObject(name)
{
}

void Background::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	stage1first.setPosition(pos);
}
void Background::SetRotation(const float r)
{
	GameObject::SetRotation(r);
	stage1first.setRotation(r);
}

void Background::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	stage1first.setScale(s);}

void Background::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	stage1first.setOrigin(o);
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
	//sea
	stage1first.setTexture(TEXTURE_MGR.Get("graphics/stage1.png"), true);

	stage1first.setOrigin(stage1first.getTexture()->getSize().x * 0.5f
		, stage1first.getTexture()->getSize().y * 0.5f);
	stage1first.setPosition({ 960.f*0.5f,0.f });

	//sky
	sky.setSize(sf::Vector2f({ 960.f, 300.f }));
	sky.setFillColor(sf::Color(211, 229, 247, 255));
	sky.setOrigin({0.f, 0.f});
	sky.setPosition({ 0.f,0.f });

	minX = 380.f;
	maxX = 580.f;
}

void Background::Update(float dt)
{
	sf::Vector2f movement(0.f, scrollSpeed * dt);

	if (InputMgr::GetKey(sf::Keyboard::Left)) 
	{
		movement.x+=moveSpeed * dt;
	}
	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		movement.x -= moveSpeed * dt;
	}
	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		movement.y -= moveSpeed * dt;
	}
	if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		movement.y -= moveSpeed * dt;
	}
	stage1first.move(movement);

	sf::Vector2f pos = stage1first.getPosition();
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	stage1first.setPosition(pos);
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(stage1first);
	window.draw(sky);
}