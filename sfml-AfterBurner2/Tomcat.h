#pragma once
#include "GameObject.h"

class Tomcat : public GameObject
{
protected:
    float minX;
    float maxX;
    float minY;
    float maxY;

    //상하 리턴
    float yClampTimer = 0.f; //clamp 끝에 닿은 누적시간
    const float returnRate = 1.f; //복귀시간
    bool yClamp = false;
    bool isReturn = false;

public:
    //tomcat
    sf::Sprite tomcat;
    std::vector<sf::Texture> textures;
    std::string texId;

    //crosshair
    sf::Sprite crosshair;
    std::string crosshairTexId;

    Tomcat(const std::string& name);
    ~Tomcat() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};