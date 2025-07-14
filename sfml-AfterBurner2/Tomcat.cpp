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
	SetPosition({ FRAMEWORK.GetWindowSizeF()*0.5f });
	SetOrigin({0.f,0.f});
	SetRotation(0.f);
}

void Tomcat::Update(float dt)
{
}

void Tomcat::Draw(sf::RenderWindow& window)
{
	window.draw(tomcat);
}