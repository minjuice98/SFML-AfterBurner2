#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	enemy.setPosition(pos);
}

void Enemy::SetRotation(const float r)
{
	GameObject::SetRotation(r);
	enemy.setRotation(r);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	enemy.setScale(s);
}

void Enemy::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	enemy.setOrigin(o);
}

void Enemy::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	enemy.setTexture(TEXTURE_MGR.Get("graphics/enemy.png"), true);
	enemy.setOrigin({ enemy.getTexture()->getSize().x*0.5f,
		enemy.getTexture()->getSize().y * 0.5f });
	enemy.setPosition({ 100.f,200.f });
	velocity = { 100.f,0.f };
	enemy.setRotation(0.f);
	
}

void Enemy::Update(float dt)
{
	sf::Vector2f pos = enemy.getPosition();
	pos += velocity * dt;
	enemy.setPosition(pos);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}