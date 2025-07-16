#include "stdafx.h"
#include "Framework.h"
#include "Tomcat.h"
#include "Background.h"
#include <direct.h>  // _getcwd()

void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);

	char buffer[256];
	_getcwd(buffer, 256);
	std::cout << "[DEBUG] Working dir: " << buffer << std::endl;

	fontIds.push_back("fonts/KOMIKAP_.ttf");

	FONT_MGR.Load(fontIds);
	TEXTURE_MGR.Load(texIds);

	InputMgr::Init();
	SCENE_MGR.Init();
}

void Framework::Do()
{
	Background background;
	background.Reset();
	
	Tomcat tomcat;
	tomcat.Reset();

	while (window.isOpen())
	{
		//시간 정리
		sf::Time dt = clock.restart();
		realDeltaTime = deltaTime = dt.asSeconds();
		deltaTime *= timeScale;
		time += deltaTime;
		realTime = realDeltaTime;

		//한 프레임 단위로 유효한 이벤트
		//ex. 매 프레임별로 검사해야 하는 경우 inputmgrUpdate
		InputMgr::Clear();
		sf::Event event;
		//Renderwinodw의 pollEvent()로 이벤트 큐 여부를 검사
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			InputMgr::UpdateEvent(event);
		}
		//메인루프에서 업데이트해야 할 목록
		SCENE_MGR.Update(deltaTime);
		//씬 검사하고, 그리기 
		window.clear();
		SCENE_MGR.Draw(window);
		window.display();
	}
}

void Framework::Release()
{
	//리소스 정리
	SCENE_MGR.Release();
	FONT_MGR.Unload(fontIds);
	TEXTURE_MGR.Unload(texIds);
}