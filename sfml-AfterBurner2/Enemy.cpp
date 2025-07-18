#include "stdafx.h"
#include "Utils.h"
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
	position = { 0.f,FRAMEWORK.GetWindowSizeF().y };
	enemy.setPosition(position); 
}

void Enemy::Update(float dt)
{
	//wave
	enemyTimer += dt;

	if (enemyTimer >= enemyRate)
	{//move
		position = { 0.f,FRAMEWORK.GetWindowSizeF().y };
		enemy.setPosition(position);
		enemyTimer = 0;
	}
	else
	{
		sf::Vector2f direction = { 1.f,-1.f };
		float speed = 200.f;
		position += direction * speed * dt;
		position.x += sin(enemyTimer * waveFrequency) * waveAmplitude * dt;
		enemy.setPosition(position);
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}