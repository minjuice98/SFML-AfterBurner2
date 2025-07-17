#include "stdafx.h"
#include "Tomcat.h"
#include "Utils.h"
#include <map>

Tomcat::Tomcat(const std::string& name)
    : GameObject(name)
{
}

void Tomcat::Init()
{
    //layer
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
}

void Tomcat::Release()
{
}

void Tomcat::Reset()
{
	//tomcat
	tomcat.setTexture(TEXTURE_MGR.Get("graphics/tomcat.png"), true);
	sf::FloatRect tomcatBounds = tomcat.getLocalBounds();
	tomcat.setOrigin(tomcatBounds.width * 0.5f, tomcatBounds.height * 0.5f);
	tomcat.setScale(4, 4);
	tomcat.setPosition({0.f, 0.f});

    minX = 380.f;
    maxX = 580.f;
    minY = 236.f;
    maxY = 436.f;

    //crosshair
    crosshair.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"), true);
    sf::FloatRect crosshairBounds = crosshair.getLocalBounds();
    crosshair.setOrigin(crosshairBounds.width * 0.5f, crosshairBounds.height * 0.5f);
    crosshair.setScale(0.05f, 0.05f);
    crosshair.setPosition(tomcat.getPosition().x, tomcat.getPosition().y - 70.f);
}

void Tomcat::Update(float dt)
{
	//tomcat move
	const float moveSpeed = 200.f;

	if (InputMgr::GetKey(sf::Keyboard::Left)) 
	{//move: sf::Transformable
		tomcat.move(-moveSpeed * dt, 0.f);
	}
	if (InputMgr::GetKey(sf::Keyboard::Right))
	{
		tomcat.move(moveSpeed * dt, 0.f);
	}
	if (InputMgr::GetKey(sf::Keyboard::Up))
	{
		tomcat.move(0.f, moveSpeed * dt);
	}
	if (InputMgr::GetKey(sf::Keyboard::Down))
	{
		tomcat.move(0.f, -moveSpeed * dt);
		tomcat.move(0.f, -moveSpeed * dt);
	}

	sf::Vector2f pos = tomcat.getPosition();
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	tomcat.setPosition({ pos.x, pos.y });

	//crosshair
	crosshair.setPosition(tomcat.getPosition().x, tomcat.getPosition().y - 70.f);
}

void Tomcat::Draw(sf::RenderWindow& window)
{
    window.draw(tomcat);
    window.draw(crosshair);
}