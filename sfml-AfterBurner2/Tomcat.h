#pragma once
#include "GameObject.h"

class Tomcat : public GameObject
{
protected:
    //tomcat
    sf::Sprite tomcat;
    std::string texId;

    float minX;
    float maxX;
    float minY;
    float maxY;

    //crosshair
    sf::Sprite crosshair;
    std::string crosshairTexId;

public:
    Tomcat(const std::string& name);
    ~Tomcat() override = default;

    void Init() override;
    void Release() override;
    void Reset() override;
    void Update(float dt) override;
    void Draw(sf::RenderWindow& window) override;
};