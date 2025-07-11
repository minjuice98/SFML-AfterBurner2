#include "Framework.h"
#include "stdafx.h"

void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);
}

void Framework::Do()
{
	while (window.isOpen())
	{
		//�ð� ����
		sf::Time dt = clock.restart();
		realDeltaTime = deltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		time += deltaTime;
		realTime = realDeltaTime;

		//�� ������ ������ ��ȿ�� �̺�Ʈ
		//ex. �� �����Ӻ��� �˻��ؾ� �ϴ� ��� inputmgrUpdate
		sf::Event event;
		//Renderwinodw�� pollEvent()�� �̺�Ʈ ť ���θ� �˻�
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//���η������� ������Ʈ�ؾ� �� ���
		//�� �˻��ϰ�, �׸��� 
	}
}

void Framework::Release()
{
	//���ҽ� ����
}
