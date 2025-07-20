#pragma once
#include "Scene.h"
class Background;
class Enemy;
class Tomcat;
class SceneGame : public Scene
{
protected:
	Background* background = nullptr;
	Enemy* enemy = nullptr;
	Tomcat* tomcat = nullptr;
	Tomcat* crosshair = nullptr;

	//enemy crosshair
	sf::Sprite enemyCrosshair; //생성 후 기본 위치 0,0
	bool isTarget = false; // 조준 중
	bool isEnemyCrossHairVisible = false; //적 조준선 표시 여부
	float enemyCrosshairTimer = 0.f;

	//enemy
	bool isEnemyHit = false;

	//explosion
	sf::Sprite explosion;
	bool isExplosionVisible; //폭파 표시 여부
	float explosionTimer = 0.f;

	//vulcan
	sf::Sprite vulcan;
	std::vector<sf::Vector2f> vulcanPositions;
	float vulcanSpeed = 500.f; 
	float fireTimer = 0.f; //누적시간 슈팅용
	float fireRate = 0.04f; 

public:
	SceneGame(SceneIds id);
	~SceneGame() override = default;   

	void Init() override;
	void Enter() override;
	void Exit() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};