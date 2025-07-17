#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name):GameObject(name)
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
	//enemy
	enemy.setTexture(TEXTURE_MGR.Get("graphics/enemy.png"), true);
	enemy.setOrigin({ enemy.getTexture()->getSize().x*0.5f,
		enemy.getTexture()->getSize().y * 0.5f });
	enemy.setScale(3, 3);
	enemy.setRotation(0.f);

	//move

}

void Enemy::Update(float dt)
{
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}