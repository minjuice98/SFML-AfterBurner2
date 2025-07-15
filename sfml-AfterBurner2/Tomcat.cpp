#include "stdafx.h"
#include "Tomcat.h"
#include "Utils.h"

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

	minX = 380.f;
	maxX = 580.f;
	minY = 236.f;
	maxY = 436.f;

}

void Tomcat::Update(float dt)
{//move: sf::Transformable
	const float moveSpeed = 200.f;
	if (InputMgr::GetKey(sf::Keyboard::Left)) //정적 멤버 함수 호출
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
		tomcat.move(0.f, -moveSpeed * dt);   
	}

	sf::Vector2f pos=tomcat.getPosition();
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	tomcat.setPosition({ pos.x, pos.y });
}

void Tomcat::Draw(sf::RenderWindow& window)
{
	window.draw(tomcat);
}