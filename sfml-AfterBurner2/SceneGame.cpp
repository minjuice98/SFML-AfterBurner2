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
	enemyCrosshair.setOrigin(enemyCrosshair.getLocalBounds().width * 0.5f,
								enemyCrosshair.getLocalBounds().height * 0.5f);
	enemyCrosshair.setScale(0.1, 0.1);

	//vulcan
	vulcan.setTexture(TEXTURE_MGR.Get("graphics/vulcan.png"));
	vulcan.setOrigin(tomcat->tomcat.getOrigin().x, tomcat->tomcat.getOrigin().y);
	vulcan.setScale(0.6f,0.6f);

	//explosion
	explosion.setTexture(TEXTURE_MGR.Get("graphics/explosion.png"));
	explosion.setOrigin(explosion.getLocalBounds().width * 0.5f,
							explosion.getLocalBounds().height * 0.5f);
	explosion.setScale(1, 1);
	isExplosionVisible = false;

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

	//폭파 후 explosion 이미지 삭제
	if (isExplosionVisible)
	{
		explosionTimer += dt;
		if (explosionTimer >= 1.0f)
		{
			isExplosionVisible = false;
		}
	}
	//respawn
	if (isEnemyHit)
	{
		enemyRespawnTimer += dt;
		if (enemyRespawnTimer >= enemyRespawnRate)
		{
			isEnemyHit = false;
			enemyRespawnTimer = 0.f;
			enemy->Reset(); // 적 리스폰
		}
	}

	//enemy crosshair 
	sf::FloatRect enemyBound = enemy->enemy.getGlobalBounds();	//bool sf::FloatRect::contains(float x, float y) const;	
	bool containCrosshair = enemyBound.contains(tomcat->crosshair.getPosition());
	bool isPressingA = InputMgr::GetKey(sf::Keyboard::A);
	
	//A를 누르지 않고 조준만 되었을 때
	if (containCrosshair && !isPressingA)
	{
		if (!isTarget)
		{
			isTarget = true;
			isEnemyCrossHairVisible = true;
			enemyCrosshairTimer = 0.f;

			sf::Vector2f enemyToCrosshair = enemy->enemy.getPosition();
			enemyCrosshair.setPosition(enemyToCrosshair.x, enemyToCrosshair.y - 50.f);
		}
		if (isEnemyCrossHairVisible) //Timer
		{
			enemyCrosshairTimer += dt;
			if (enemyCrosshairTimer >= 1.0f)
			{
				isEnemyCrossHairVisible = false;
				isTarget = false;
			}
		}
	}
	//A를 누르고 있고 enemybound가 crosshair를 포함하는 경우
	else if(!isEnemyHit&&isPressingA&&containCrosshair)
	{
		if (!isTarget)
		{
			isTarget = true;
			isEnemyCrossHairVisible = true;
			enemyCrosshairTimer = 0.f;

			sf::Vector2f enemyToCrosshair = enemy->enemy.getPosition();
			enemyCrosshair.setPosition(enemyToCrosshair.x, enemyToCrosshair.y - 50.f);
		}
		
		if (isEnemyCrossHairVisible)
		{
			isEnemyCrossHairVisible = false;
			isTarget = false;

			//explosion
			isEnemyHit = true;
			isExplosionVisible = true;
			explosionTimer = 0.f;
			explosion.setPosition(enemy->enemy.getPosition());
		}
	}
	else if (!containCrosshair)
	{
		isTarget = false;
		isEnemyCrossHairVisible = false;
		enemyCrosshairTimer = 0.f;
	}

	//vulcan
	fireTimer += dt; //발사 후 경과시간
	if (isPressingA && fireTimer >= fireRate)
	{
		//Left
		vulcanPositions.push_back({ tomcat->tomcat.getPosition().x - 50.f,
			tomcat->tomcat.getPosition().y - 20.f });
		//Right
		vulcanPositions.push_back({ tomcat->tomcat.getPosition().x + 12.f,
			tomcat->tomcat.getPosition().y - 20.f });
		fireTimer = 0.f;
	}
	for (auto it = vulcanPositions.begin(); it != vulcanPositions.end();)
	{
		it->y -= vulcanSpeed * dt * 0.8f;
		if (it->y < -50.f)
		{
			it = vulcanPositions.erase(it);
		}
		else ++it;
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	//window.setView(worldView);
	Scene::Draw(window);
	background->Draw(window);
	if (!isEnemyHit) enemy->Draw(window);
	if (isExplosionVisible)window.draw(explosion);
	for (const auto& pos : vulcanPositions)
	{
		vulcan.setPosition(pos);
		window.draw(vulcan);
	}
	if (isEnemyCrossHairVisible) window.draw(enemyCrosshair);
	tomcat->Draw(window);
}