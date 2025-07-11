#include "stdafx.h"
#include "InputMgr.h"

//static std::vector<bool> heldKeys;
//static std::vector<bool> upKeys;
//static std::vector<bool> downKeys;

void InputMgr::Init()
{
	//벡터 사이즈 지정, false 초기화
	heldKeys.resize(sf::Keyboard::KeyCount, false);
	upKeys.resize(sf::Keyboard::KeyCount, false);
	downKeys.resize(sf::Keyboard::KeyCount, false);
}
void InputMgr::Clear() 
{	//크기 변경 할 필요 없이 요소 값만 변경
	std::fill(upKeys.begin(), upKeys.end(), false);
	std::fill(downKeys.begin(), downKeys.end(), false);
	//이전 프레임 유지
	//std::fill(heldKeys.begin(), heldKeys.end(), false);
}
void InputMgr::UpdateEvent(const sf::Event& ev) 
{	//press, release
	switch (ev.type)
	{
	case sf::Event::KeyPressed:
		if (!heldKeys[ev.key.code])
		{
			downKeys[ev.key.code] = true;
			heldKeys[ev.key.code] = true;
		}
		break;
	case sf::Event::KeyReleased:
		downKeys[ev.key.code] = false;
		upKeys[ev.key.code] = true;
		break;
	}
}
bool InputMgr::GetKeyDown(sf::Keyboard::Key key)
{
	return downKeys[key];
}
bool InputMgr::GetKeyUp(sf::Keyboard::Key key)
{
	return upKeys[key];
}
bool InputMgr::GetKey(sf::Keyboard::Key key)
{
	return heldKeys[key];
}