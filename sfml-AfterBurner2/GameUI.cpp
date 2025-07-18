#include "stdafx.h"
#include "GameUI.h"

GameUI::GameUI(const std::string& name)
{
}

void GameUI::Init()
{
	sortingLayer = SortingLayers::UI;
	sortingOrder = 3;
}

void GameUI::Release()
{
}

void GameUI::Reset()
{
	scoreIcon.setTexture(TEXTURE_MGR.Get("graphics/tomcat.png"), true);
	scoreIcon.setOrigin({ scoreIcon.getTexture()->getSize().x * 0.5f, 
							scoreIcon.getTexture()->getSize().y * 0.5f});
	scoreIcon.setScale(1, 1);
	scoreIcon.setPosition({ 50.f, 50.f });
}

void GameUI::Update(float dt)
{
}

void GameUI::Draw(sf::RenderWindow& window)
{
	window.draw(scoreIcon);
}   