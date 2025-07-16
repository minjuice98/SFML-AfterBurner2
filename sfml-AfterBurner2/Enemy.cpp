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
	enemy.setPosition({ 100.f,300.f });
	enemy.setRotation(0.f);

	//move
	isLeft = !isLeft;
	if (!isLeft)
	{
		startPos = { 50.f,620.f };
		endPos = { 910.f,100.f };
	}
	else
	{
		startPos = { 910.f,620.f };
		endPos = { 50.f,100.f };
	}
	accTime = 0.f;
	enemy.setPosition(startPos);
}

void Enemy::Update(float dt)
{
	accTime += dt;
	float t = std::min(accTime / moveTime, 1.f);

	// 선형 보간으로 x 좌표 계산
	float x = Utils::Lerp(startPos.x, endPos.x, t);

	// 포물선 궤도 계산 (올바른 공식)
	float midX = (startPos.x + endPos.x) * 0.5f;
	float highHeight = -200.f;

	// 포물선 공식: y = a(x - midX)² + maxHeight
	float a = highHeight / ((startPos.x - midX) * (startPos.x - midX));
	float maxHeight = std::max(startPos.y, endPos.y) + highHeight;
	float y = a * (x - midX) * (x - midX) + maxHeight;

	enemy.setPosition({ x, y });

	// 이동 완료 시 리셋
	if (t >= 1.f)
	{
		Reset();
	}
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(enemy);
}