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
    //layer
    sortingLayer = SortingLayers::Foreground;
    sortingOrder = 1;
}

void Tomcat::Release()
{
}

void Tomcat::Reset()
{
	//tomcat
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

	tomcat.setTexture(textures[7], true);
	sf::FloatRect tomcatBounds = tomcat.getLocalBounds();
	tomcat.setOrigin(tomcatBounds.width * 0.5f, tomcatBounds.height * 0.5f);
	tomcat.setScale(4, 4);
	tomcat.setPosition({0.f, 0.f});

    minX = 380.f;
    maxX = 580.f;
    minY = 236.f;
    maxY = 436.f;

    //crosshair
    crosshair.setTexture(TEXTURE_MGR.Get("graphics/crosshair.png"), true);
    sf::FloatRect crosshairBounds = crosshair.getLocalBounds();
    crosshair.setOrigin(crosshairBounds.width * 0.5f, crosshairBounds.height * 0.5f);
    crosshair.setScale(0.05f, 0.05f);
    crosshair.setPosition(tomcat.getPosition().x, tomcat.getPosition().y - 70.f);
}

void Tomcat::Update(float dt)
{
	//axis inputmgr
	float horizontalInput = InputMgr::GetAxis(Axis::Horizontal);
	float verticalInput = InputMgr::GetAxis(Axis::Vertical);

	//tomcat move
	const float moveSpeed = 200.f;
	sf::Vector2f moveDir(horizontalInput, -verticalInput);
	tomcat.move(moveDir * moveSpeed * dt);

	//if (InputMgr::GetKey(sf::Keyboard::Left)) 
	//{//move: sf::Transformable
	//	tomcat.move(-moveSpeed * dt, 0.f);
	//}
	//if (InputMgr::GetKey(sf::Keyboard::Right))
	//{
	//	tomcat.move(moveSpeed * dt, 0.f);
	//}
	//if (InputMgr::GetKey(sf::Keyboard::Up))
	//{
	//	tomcat.move(0.f, moveSpeed * dt);
	//}
	//if (InputMgr::GetKey(sf::Keyboard::Down))
	//{
	//	tomcat.move(0.f, -moveSpeed * dt);
	//	tomcat.move(0.f, -moveSpeed * dt);
	//}
	
	//clamp
	sf::Vector2f pos = tomcat.getPosition();
	pos.x = Utils::Clamp(pos.x, minX, maxX);
	pos.y = Utils::Clamp(pos.y, minY, maxY);
	tomcat.setPosition(pos);

	//axis
	float horizontal = horizontalInput * 2.5f; // -2.5 ~ 2.5
	float vertical = verticalInput * 1.5f; // -1.5 ~ 1.5
	
	//좌우
	int col = 2; //초기화
	if (horizontal <= -1.5f) col = 0; //-2.5 ~ -1.5
	else if (horizontal <= -0.5f) col = 1; //-1.5 ~ -0.5
	else if (horizontal <= 0.5f) col = 2; //-0.5 ~ 0.5
	else if (horizontal <= 1.5f) col = 3; //0.5 ~ 1.5
	else col = 4; //1.5 ~ 2.5

	//상하 
	int row = 1; // 초기화
	if (vertical <= -0.5f) row = 0; //-1.5 ~ -0.5
	else if (vertical <= 0.5f) row = 1;  //-0.5 ~ 0.5
	else row = 2; //0.5 ~ 1.5

	//yClamp
	if (row == 0 || row == 2)
	{
		std::cout << "At clamp end! row: " << row << ", yClampTimer: " << yClampTimer << std::endl;
		if (!yClamp)
		{
			yClamp = true;
			yClampTimer = 0.f;
		}
		
		yClampTimer += dt;
		if (yClampTimer >= returnRate)
		{
			isReturn = true;
			yClamp = false;
			yClampTimer = 0.f;
		}
	}
	else
	{
		yClamp = false;
		yClampTimer = 0.f;
		isReturn = false;
	}

	if (isReturn) row = 1;

	//sprite
	int spriteIndex = row * 5 + col;
	tomcat.setTexture(textures[spriteIndex], true);

	//crosshair
	crosshair.setPosition(tomcat.getPosition().x, tomcat.getPosition().y - 70.f);
}

void Tomcat::Draw(sf::RenderWindow& window)
{
    window.draw(tomcat);
    window.draw(crosshair);
}