#pragma once
#include "GameObject.h"

class Tomcat : public GameObject
{
protected:
    sf::Sprite tomcat;
    std::vector<sf::Texture> textures;
    float minX, maxX;
    float minY, maxY;

    // 스프라이트 방향 관리
    int currentSpriteIndex = 7; // 현재 스프라이트 인덱스 (중심: 7)
    int targetSpriteIndex = 7;  // 목표 스프라이트 인덱스

    // 타이밍 관리
    float spriteChangeTimer = 0.f;
    const float spriteChangeInterval = 0.15f; // 스프라이트 변경 간격 (초)

    // 경계 충돌 시 복귀 타이머
    float boundaryTimer = 0.f;
    const float boundaryReturnDelay = 0.3f; // 경계에서 복귀 시작까지 대기 시간
    bool isTouchingBoundary = false;

    // 방향별 스프라이트 경로 정의
    struct DirectionPath {
        std::vector<int> path;
    };

    std::map<int, DirectionPath> directionPaths; // 방향별 경로 저장

    void InitDirectionPaths();
    void UpdateSpriteDirection(int dx, int dy, float dt);
    void UpdateSpriteAnimation(float dt);
    int GetDirectionIndex(int dx, int dy);

public:
    Tomcat(const std::string& name = "");
    ~Tomcat() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};




//#pragma once
//#include "GameObject.h"
//class Tomcat :public GameObject
//{
//protected:
//	sf::Sprite tomcat;
//	std::vector < sf::Texture > textures;
//
//	float minX, maxX;
//	float minY, maxY;
//
//	float currentAngle = 0.f; //현재 방향 각도
//	const float smoothing = 10.f; //복귀 속도 조절 계수
//	const int totalDirections = 15; //방향 개수
//	const float degPerStep = 360.f / 15; //24도
//
//public:
//	Tomcat(const std::string& name="");
//	~Tomcat() override = default;
//
//	// GameObject을(를) 통해 상속됨
//	void Init() override;
//	void Release() override;
//	void Reset() override;
//	void Update(float dt) override;
//	void Draw(sf::RenderWindow& window) override;
//};