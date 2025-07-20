#include "stdafx.h"
#include "Background.h"

Background::Background(const std::string& name) : GameObject(name)
{
}

void Background::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	stage1first.setPosition(pos);
	stage1second.setPosition(pos.x, pos.y - backgroundHeight);
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
	backgroundHeight = stage1first.getTexture()->getSize().y;
	stage1first.setOrigin(stage1first.getTexture()->getSize().x * 0.5f, 0.f);
	stage1first.setPosition({ 960.f*0.5f,0.f });

	stage1second.setTexture(TEXTURE_MGR.Get("graphics/stage1.png"), true);
	stage1second.setOrigin(stage1second.getTexture()->getSize().x * 0.5f, 0.f);
	stage1second.setPosition({ 960.f * 0.5f, -backgroundHeight });

	//sky
	sky.setSize(sf::Vector2f({ 960.f, 400.f }));
	sky.setFillColor(sf::Color(80, 188, 233, 255));
	sky.setOrigin({0.f, 0.f});
	sky.setPosition({ 0.f,0.f });

	horizon.setSize(sf::Vector2f({ 960.f, 100.f }));
	horizon.setFillColor(sf::Color(255, 255, 255, 120));
	horizon.setOrigin({ 0.f, 0.f });
	horizon.setPosition({ 0.f, 300.f });

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
	stage1second.move(movement);

	//반복 스크롤
	if (stage1first.getPosition().y >= backgroundHeight) {
		stage1first.setPosition(stage1first.getPosition().x, stage1second.getPosition().y - backgroundHeight);
	}
	if (stage1second.getPosition().y >= backgroundHeight) {
		stage1second.setPosition(stage1second.getPosition().x, stage1first.getPosition().y - backgroundHeight);
	}

	sf::Vector2f pos1 = stage1first.getPosition();
	sf::Vector2f pos2 = stage1second.getPosition();
	pos1.x = Utils::Clamp(pos1.x, minX, maxX);
	pos2.x = Utils::Clamp(pos2.x, minX, maxX);
	stage1first.setPosition(pos1);
	stage1second.setPosition(pos2);
}

void Background::Draw(sf::RenderWindow& window)
{
	window.draw(stage1first);
	window.draw(stage1second);
	window.draw(sky);
	window.draw(horizon);
}