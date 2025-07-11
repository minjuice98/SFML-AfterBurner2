#pragma once
#include "Singleton.h"
#include "stdafx.h"

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	//싱글톤 상속 생성자
	Framework() = default;
	~Framework() override = default;

	//창 관리, RenderWindow 객체 window
	sf::RenderWindow window;

	//시간 관리
	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f; //조정시간
	//게임 세계 논리적 경과 시간, time+=deltaTime
	float deltaTime = 0.f;
	//en 두 프레임 사이 조정된 간격
	
	float realTime = 0.f; //실제시간
	//Clock 시작 이후 총 경과된 시간 asSecond() 등으로 얻음
	float realDeltaTime = 0.f;
	//실제 델타 시간, 두 프레임 사이의 실제 경과 시간

	bool pause = false; //일시정지 시 사용

	//리소스 관리
	std::vector<std::string> texIds;
	std::vector<std::string> fontIds;
	std::vector<std::string> soundIds;

public:
	//윈도우 객체를 반환하는 함수
	sf::RenderWindow& GetWindow() { return window; }
	//2u: unsinged int, 2i:int
	//정수형으로 반환
	sf::Vector2u GetWindowSize() const { return window.getSize(); }
	//실수형으로 반환
	sf::Vector2f GetWindowSizeF() const { return (sf::Vector2f)window.getSize(); }
	//사각형 형태로 반환
	sf::FloatRect GetWindowBounds() const
	{//왼쪽상단모서리 x,y,너비,높이
		sf::Vector2f size = GetWindowSizeF();
		return sf::FloatRect(0.f, 0.f, size.x, size.y);
	}

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }
	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }

	//창 생성
	virtual void Init(int w, int h, const std::string& t);
	virtual void Do();
	virtual void Release();
};
#define FRAMEWORK (Framework::Instance())
//호출하는 순간 Framework 싱글톤 객체 생성