#include "stdafx.h"
#include "SceneGame.h"
#include "Background.h"
#include "Enemy.h"
#include "Tomcat.h"

SceneGame::SceneGame(SceneIds id) : Scene(SceneIds::Game)
{
}

void SceneGame::Init()
{
	texIds.push_back("graphics/stage1.png");
	texIds.push_back("graphics/enemy.png");
	texIds.push_back("graphics/tomcat.png");
	texIds.push_back("graphics/crosshair.png");
	texIds.push_back("graphics/explosion.png");
	texIds.push_back("graphics/vulcan.png");
	TEXTURE_MGR.Load(texIds);
	
	background = (Background*)AddGameObject(new Background("Background"));
	enemy = (Enemy*)AddGameObject(new Enemy("Enemy"));
	tomcat = (Tomcat*)AddGameObject(new Tomcat("Tomcat"));
	crosshair= (Tomcat*)AddGameObject(new Tomcat("crosshair"));

	//enemy crosshair
	enemyCrosshair.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"));
	enemyCrosshair.setOrigin({ 0.f,0.f });
	enemyCrosshair.setScale(0.1, 0.1);

	//vulcan
	vulcan.setTexture(TEXTURE_MGR.Get("graphics/vulcan.png"));
	vulcan.setOrigin(tomcat->tomcat.getOrigin().x, tomcat->tomcat.getOrigin().y);
	vulcan.setScale(0.6f,0.6f);

	//explosion
	explosion.setTexture(TEXTURE_MGR.Get("graphics/explosion.png"));
	explosion.setOrigin(enemy->enemy.getPosition().x, enemy->enemy.getPosition().y);
	explosion.setScale(1, 1);

	Scene::Init();
}

void SceneGame::Enter()
{
	sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
	//worldView.setSize(windowSize); //창 크기에 맞추어 초기화
	//worldView.setCenter(tomcat->GetPosition());
	
	Scene::Enter();
}

void SceneGame::Exit()
{
	Scene::Exit();
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	//worldView.setCenter(tomcat->GetPosition());

	//enemy crosshair 
	sf::FloatRect enemyBound = enemy->enemy.getGlobalBounds();
	//bool sf::FloatRect::contains(float x, float y) const;
	//bool sf::FloatRect::contains(const sf::Vector2f & point) const;
	if (enemyBound.contains(tomcat->crosshair.getPosition()))
	{
		target = true;
		std::cout << "crosshair!";
		enemyCrosshair.setPosition(enemy->enemy.getPosition());
	}
	else target = false;

	//vulcan
	fireTimer += dt; //발사 후 경과시간
	//
	if (InputMgr::GetKey(sf::Keyboard::A)&&fireTimer>=fireRate)
	{   
		//Left
		vulcanPositions.push_back({ tomcat->tomcat.getPosition().x - 50.f,
			tomcat->tomcat.getPosition().y - 20.f });
		//Right
		vulcanPositions.push_back({ tomcat->tomcat.getPosition().x + 12.f,
			tomcat->tomcat.getPosition().y - 20.f });

		fireTimer = 0.f;
	}

	for (auto& pos : vulcanPositions)
	{
		pos.y -= vulcanSpeed * dt * 0.8;

		//explosion
		if (enemyBound.contains(pos))
		{
			target = true;
			explosion.setPosition(enemy->enemy.getPosition());
		}
		else target = false;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	//window.setView(worldView);
	Scene::Draw(window);
	background->Draw(window);
	enemy->Draw(window);
	if (target) window.draw(explosion);
	for (auto pos : vulcanPositions)
	{
		vulcan.setPosition(pos);
		window.draw(vulcan);
	}
	if (target) window.draw(enemyCrosshair);
	tomcat->Draw(window);
}