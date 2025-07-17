#pragma once
#include "GameObject.h"

class Tomcat : public GameObject
{
protected:
    float minX;
    float maxX;
    float minY;
    float maxY;
public:
    //tomcat
    sf::Sprite tomcat;
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