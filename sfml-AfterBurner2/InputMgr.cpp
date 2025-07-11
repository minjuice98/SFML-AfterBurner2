#include "stdafx.h"
#include "InputMgr.h"

//static std::vector<bool> heldKeys;
//static std::vector<bool> upKeys;
//static std::vector<bool> downKeys;

void InputMgr::Init()
{
	//���� ������ ����, false �ʱ�ȭ
	heldKeys.resize(sf::Keyboard::KeyCount, false);
	upKeys.resize(sf::Keyboard::KeyCount, false);
	downKeys.resize(sf::Keyboard::KeyCount, false);
}
void InputMgr::Clear() 
{	//ũ�� ���� �� �ʿ� ���� ��� ���� ����
	std::fill(upKeys.begin(), upKeys.end(), false);
	std::fill(downKeys.begin(), downKeys.end(), false);
	//���� ������ ����
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