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
    textures.resize(15);

    std::vector<std::string> fileNames = {
        "000", "001", "002", "003", "004",
        "005", "006", "007", "008", "009",
        "010", "011", "012", "013", "014"
    };

    for (int i = 0; i < fileNames.size(); ++i)
    {
        std::string fileName = "graphics/tomcat" + fileNames[i] + ".png";
        textures[i].loadFromFile(fileName);
    }

    tomcat.setTexture(textures[7]);
    tomcat.setOrigin({ 0.f, 0.f });

    InitDirectionPaths();
}

void Tomcat::InitDirectionPaths()
{
    // 각 방향별 스프라이트 경로 정의
    // 3x5 그리드: 0-4 (상단), 5-9 (중간), 10-14 (하단)
    // 중심은 7번 (2행, 2열)

    directionPaths[-1] = { {7, 6, 5} };      // 좌 (7→6→5)
    directionPaths[1] = { {7, 8, 9} };       // 우 (7→8→9)
    directionPaths[-2] = { {7, 2} };         // 상 (7→2)
    directionPaths[2] = { {7, 12} };         // 하 (7→12)
    directionPaths[-3] = { {7, 1, 0} };      // 좌상 (7→1→0)
    directionPaths[-4] = { {7, 3, 4} };      // 우상 (7→3→4)
    directionPaths[3] = { {7, 11, 10} };     // 좌하 (7→11→10)
    directionPaths[4] = { {7, 13, 14} };     // 우하 (7→13→14)
}

void Tomcat::Release()
{
}

void Tomcat::Reset()
{
    tomcat.setPosition({ FRAMEWORK.GetWindowSizeF() * 0.5f });
    tomcat.setRotation(0.f);
    minX = 380.f;
    maxX = 580.f;
    minY = 236.f;
    maxY = 436.f;

    currentSpriteIndex = 7;
    targetSpriteIndex = 7;
    spriteChangeTimer = 0.f;
    boundaryTimer = 0.f;
    isTouchingBoundary = false;
}

int Tomcat::GetDirectionIndex(int dx, int dy)
{
    // 방향 조합을 고유 인덱스로 변환
    if (dx == -1 && dy == 0) return -1;    // 좌
    if (dx == 1 && dy == 0) return 1;      // 우
    if (dx == 0 && dy == -1) return -2;    // 상
    if (dx == 0 && dy == 1) return 2;      // 하
    if (dx == -1 && dy == -1) return -3;   // 좌상
    if (dx == 1 && dy == -1) return -4;    // 우상
    if (dx == -1 && dy == 1) return 3;     // 좌하
    if (dx == 1 && dy == 1) return 4;      // 우하
    return 0; // 중심 (입력 없음)
}

void Tomcat::UpdateSpriteDirection(int dx, int dy, float dt)
{
    int directionIndex = GetDirectionIndex(dx, dy);

    if (directionIndex == 0)
    {
        // 입력이 없으면 중심으로 복귀
        targetSpriteIndex = 7;
    }
    else
    {
        // 해당 방향의 경로가 존재하는지 확인
        if (directionPaths.find(directionIndex) != directionPaths.end())
        {
            const auto& path = directionPaths[directionIndex].path;

            // 현재 스프라이트가 경로 상에 있는지 확인
            bool onPath = false;
            int currentPathIndex = 0;

            for (int i = 0; i < path.size(); ++i)
            {
                if (path[i] == currentSpriteIndex)
                {
                    onPath = true;
                    currentPathIndex = i;
                    break;
                }
            }

            if (onPath)
            {
                // 경로 상에 있다면 다음 단계로 진행
                if (currentPathIndex < path.size() - 1)
                {
                    targetSpriteIndex = path[currentPathIndex + 1];
                }
                else
                {
                    // 이미 마지막 단계라면 그대로 유지
                    targetSpriteIndex = currentSpriteIndex;
                }
            }
            else
            {
                // 경로 상에 없다면 중심에서 시작
                if (currentSpriteIndex == 7)
                {
                    targetSpriteIndex = path[1]; // 첫 번째 방향 스프라이트
                }
                else
                {
                    // 다른 방향에서 왔다면 먼저 중심으로
                    targetSpriteIndex = 7;
                }
            }
        }
    }
}

void Tomcat::UpdateSpriteAnimation(float dt)
{
    spriteChangeTimer += dt;

    if (spriteChangeTimer >= spriteChangeInterval)
    {
        spriteChangeTimer = 0.f;

        if (currentSpriteIndex != targetSpriteIndex)
        {
            // 중심(7)으로 복귀하는 경우
            if (targetSpriteIndex == 7)
            {
                // 각 방향의 경로를 역순으로 따라가기
                bool found = false;
                for (const auto& pair : directionPaths)
                {
                    const auto& path = pair.second.path;

                    // 현재 스프라이트가 이 경로에 있는지 확인
                    for (int i = 0; i < path.size(); ++i)
                    {
                        if (path[i] == currentSpriteIndex)
                        {
                            if (i > 0)
                            {
                                // 이전 단계로 이동
                                currentSpriteIndex = path[i - 1];
                            }
                            found = true;
                            break;
                        }
                    }
                    if (found) break;
                }

                if (!found)
                {
                    // 경로를 찾지 못했다면 직접 중심으로
                    currentSpriteIndex = 7;
                }
            }
            else
            {
                // 목표 방향으로 이동
                currentSpriteIndex = targetSpriteIndex;
            }

            // 텍스처 업데이트
            tomcat.setTexture(textures[currentSpriteIndex]);
        }
    }
}

void Tomcat::Update(float dt)
{
    const float moveSpeed = 200.f;
    int dx = 0;
    int dy = 0;

    if (InputMgr::GetKey(sf::Keyboard::Left)) dx -= 1;
    if (InputMgr::GetKey(sf::Keyboard::Right)) dx += 1;
    if (InputMgr::GetKey(sf::Keyboard::Up)) dy -= 1;
    if (InputMgr::GetKey(sf::Keyboard::Down)) dy += 1;

    // 이동 처리
    tomcat.move(dx * moveSpeed * dt, dy * moveSpeed * dt);

    // 경계 처리
    sf::Vector2f pos = tomcat.getPosition();
    sf::Vector2f originalPos = pos;

    pos.x = Utils::Clamp(pos.x, minX, maxX);
    pos.y = Utils::Clamp(pos.y, minY, maxY);
    tomcat.setPosition(pos);

    // 경계 충돌 감지
    bool hitBoundary = (originalPos.x != pos.x || originalPos.y != pos.y);

    if (hitBoundary && (dx != 0 || dy != 0))
    {
        if (!isTouchingBoundary)
        {
            isTouchingBoundary = true;
            boundaryTimer = 0.f;
        }
        else
        {
            boundaryTimer += dt;
        }
    }
    else
    {
        isTouchingBoundary = false;
        boundaryTimer = 0.f;
    }

    // 스프라이트 방향 업데이트
    if (isTouchingBoundary && boundaryTimer >= boundaryReturnDelay)
    {
        // 경계에서 일정 시간 후 중심으로 복귀
        UpdateSpriteDirection(0, 0, dt);
    }
    else
    {
        // 일반적인 방향 업데이트
        UpdateSpriteDirection(dx, dy, dt);
    }

    // 스프라이트 애니메이션 업데이트
    UpdateSpriteAnimation(dt);
}

void Tomcat::Draw(sf::RenderWindow& window)
{
    window.draw(tomcat);
}



//#include "stdafx.h"
//#include "Tomcat.h"
//#include "Utils.h"
//Tomcat::Tomcat(const std::string& name)
//	:GameObject(name)
//{
//}
//
//void Tomcat::Init()
//{
//	textures.resize(15);
//	
//	std::vector<std::string> fileNames = {
//	"000", "001", "002", "003", "004",
//	"005", "006", "007", "008", "009",
//	"010", "011", "012", "013", "014"
//	};
//
//	for (int i = 0; i < fileNames.size(); ++i)
//	{
//		std::string fileName = "graphics/tomcat" + fileNames[i] + ".png";
//		textures[i].loadFromFile(fileName);
//	}
//
//	tomcat.setTexture(textures[7]);
//	tomcat.setOrigin({ 0.f,0.f });
//}
//
//void Tomcat::Release()
//{
//}
//
//void Tomcat::Reset()
//{
//	tomcat.setPosition({ FRAMEWORK.GetWindowSizeF()*0.5f });
//	tomcat.setRotation(0.f);
//
//	minX = 380.f;
//	maxX = 580.f;
//	minY = 236.f;
//	maxY = 436.f;
//
//}
//void Tomcat::Update(float dt)
//{
//	const float moveSpeed = 200.f;
//	int dx = 0;
//	int dy = 0;
//
//	if (InputMgr::GetKey(sf::Keyboard::Left)) dx -= 1;
//	if (InputMgr::GetKey(sf::Keyboard::Right)) dx += 1;
//	if (InputMgr::GetKey(sf::Keyboard::Up)) dy -= 1;
//	if (InputMgr::GetKey(sf::Keyboard::Down)) dy += 1;
//
//	tomcat.move(dx * moveSpeed * dt, dy * moveSpeed * dt);
//
//	sf::Vector2f pos=tomcat.getPosition();
//	pos.x = Utils::Clamp(pos.x, minX, maxX);
//	pos.y = Utils::Clamp(pos.y, minY, maxY);
//	tomcat.setPosition(pos);
//
//	// --- 방향 각도 계산 및 복귀 처리 --- 
//
//	if (dx != 0 || dy != 0)
//	{
//		// 방향 입력이 있을 경우: 해당 방향의 각도를 계산
//		float angleRad = std::atan2(static_cast<float>(dy), static_cast<float>(dx));
//		float angleDeg = angleRad * 180.f / 3.141592f;
//
//		// -180 ~ +180 범위 → 0 ~ 360 범위로 변환
//		if (angleDeg < 0)
//			angleDeg += 360.f;
//
//		currentAngle = angleDeg; // 현재 방향을 저장
//	}
//	else
//	{
//		// 각도 차이를 -180~180 범위로 맞춤
//		float target = 0.f;
//		float diff = target - currentAngle;
//
//		while (diff < -180.f) diff += 360.f;
//		while (diff > 180.f) diff -= 360.f;
//
//		currentAngle += diff * smoothing * dt;
//
//		if (currentAngle < 0.f) currentAngle += 360.f;
//		else if (currentAngle >= 360.f) currentAngle -= 360.f;
//	}
//
//
//	// 각도 → 방향 인덱스 변환 (오프셋 적용)
//	const int centerIndex = 7;
//	int rawIndex = static_cast<int>(std::round(currentAngle / degPerStep)) % totalDirections;
//	int index = (rawIndex + centerIndex) % totalDirections;
//
//	tomcat.setTexture(textures[index]);
//}
//
//
//
//
//void Tomcat::Draw(sf::RenderWindow& window)
//{
//	window.draw(tomcat);
//}

//void Tomcat::Update(float dt)
//{	//move: sf::Transformable
//	const float moveSpeed = 200.f;
//	if (InputMgr::GetKey(sf::Keyboard::Left)) //정적 멤버 함수 호출
//	{
//		tomcat.move(-moveSpeed * dt, 0.f);
//	}
//	if (InputMgr::GetKey(sf::Keyboard::Right))
//	{
//		tomcat.move(moveSpeed * dt, 0.f);
//	}
//	if (InputMgr::GetKey(sf::Keyboard::Up))
//	{
//		tomcat.move(0.f, moveSpeed * dt);
//	}
//	if (InputMgr::GetKey(sf::Keyboard::Down))
//	{
//		tomcat.move(0.f, -moveSpeed * dt);   
//	}
//
//	sf::Vector2f pos=tomcat.getPosition();
//	pos.x = Utils::Clamp(pos.x, minX, maxX);
//	pos.y = Utils::Clamp(pos.y, minY, maxY);
//	tomcat.setPosition({ pos.x, pos.y });
//}