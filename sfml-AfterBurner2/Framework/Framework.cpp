#include "stdafx.h"
#include "Framework.h"
#include "Tomcat.h"

void Framework::Init(int w, int h, const std::string& t)
{
	window.create(sf::VideoMode(w, h), t);
	//여러 개 로드하는 경우 프레임웍에서 로드
	
	texIds.push_back("graphics/tomcat.png");
	TEXTURE_MGR.Load(texIds);

}

void Framework::Do()
{
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
		//씬 검사하고, 그리기 
		window.clear();
		tomcat.Draw(window);
		window.display();
	}
}

void Framework::Release()
{
	//리소스 정리
}