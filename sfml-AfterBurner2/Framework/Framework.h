#pragma once
#include "Singleton.h"
#include "stdafx.h"

class Framework : public Singleton<Framework>
{
	friend Singleton<Framework>;

protected:
	//�̱��� ��� ������
	Framework() = default;
	~Framework() override = default;

	//â ����, RenderWindow ��ü window
	sf::RenderWindow window;

	//�ð� ����
	sf::Clock clock;
	float timeScale = 1.f;

	float time = 0.f; //�����ð�
	//���� ���� ���� ��� �ð�, time+=deltaTime
	float deltaTime = 0.f;
	//en �� ������ ���� ������ ����
	
	float realTime = 0.f; //�����ð�
	//Clock ���� ���� �� ����� �ð� asSecond() ������ ����
	float realDeltaTime = 0.f;
	//���� ��Ÿ �ð�, �� ������ ������ ���� ��� �ð�

	bool pause = false; //�Ͻ����� �� ���

	//���ҽ� ����
	std::vector<std::string> texIds;
	std::vector<std::string> fontIds;
	std::vector<std::string> soundIds;

public:
	//������ ��ü�� ��ȯ�ϴ� �Լ�
	sf::RenderWindow& GetWindow() { return window; }
	//2u: unsinged int, 2i:int
	//���������� ��ȯ
	sf::Vector2u GetWindowSize() const { return window.getSize(); }
	//�Ǽ������� ��ȯ
	sf::Vector2f GetWindowSizeF() const { return (sf::Vector2f)window.getSize(); }
	//�簢�� ���·� ��ȯ
	sf::FloatRect GetWindowBounds() const
	{//���ʻ�ܸ𼭸� x,y,�ʺ�,����
		sf::Vector2f size = GetWindowSizeF();
		return sf::FloatRect(0.f, 0.f, size.x, size.y);
	}

	float GetTimeScale() const { return timeScale; }
	void SetTimeScale(float scale) { timeScale = scale; }
	float GetTime() const { return time; }
	float GetDeltaTime() const { return deltaTime; }
	float GetRealTime() const { return realTime; }
	float GetRealDeltaTime() const { return realDeltaTime; }

	//â ����
	virtual void Init(int w, int h, const std::string& t);
	virtual void Do();
	virtual void Release();
};
#define FRAMEWORK (Framework::Instance())
//ȣ���ϴ� ���� Framework �̱��� ��ü ����