#include "stdafx.h"
#include "Tomcat.h"

Tomcat::Tomcat(const std::string& name)
	:GameObject(name)
{
}

void Tomcat::Init()
{
}

void Tomcat::Release()
{
}

void Tomcat::Reset()
{
	tomcat.setTexture(TEXTURE_MGR.Get(texId), true);
	tomcat.setPosition({ FRAMEWORK.GetWindowSizeF()*0.5f });
	tomcat.setOrigin({0.f,0.f});
	tomcat.setRotation(0.f);
}

void Tomcat::Update(float dt)
{
	const float moveSpeed = 200.f;
	if (InputMgr::GetKey(sf::Keyboard::Left))
	{
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
		tomcat.move(0.f ,-moveSpeed * dt);
	}
}

void Tomcat::Draw(sf::RenderWindow& window)
{
	window.draw(tomcat);
}