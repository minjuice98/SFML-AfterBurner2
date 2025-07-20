#include "stdafx.h"
#include "InputMgr.h"

std::vector<bool> InputMgr::heldKeys;
std::vector<bool> InputMgr::upKeys;
std::vector<bool> InputMgr::downKeys;
std::unordered_map<Axis, AxisInfo> InputMgr::axisInfoMap;

void InputMgr::Init()
{
	//벡터 사이즈 지정, false 초기화
	heldKeys.resize(sf::Keyboard::KeyCount, false);
	upKeys.resize(sf::Keyboard::KeyCount, false);
	downKeys.resize(sf::Keyboard::KeyCount, false);

	//Axis
	AxisInfo infoH;
	infoH.axis = Axis::Horizontal;
	infoH.positives.push_back(sf::Keyboard::Right);
	infoH.negatives.push_back(sf::Keyboard::Left);
	axisInfoMap[Axis::Horizontal] = infoH;

	AxisInfo infoV;
	infoV.axis = Axis::Vertical;
	infoV.positives.push_back(sf::Keyboard::Down);
	infoV.negatives.push_back(sf::Keyboard::Up);
	axisInfoMap[Axis::Vertical] = infoV;
}
void InputMgr::Clear() 
{	//크기 변경 할 필요 없이 요소 값만 변경
	std::fill(upKeys.begin(), upKeys.end(), false);
	std::fill(downKeys.begin(), downKeys.end(), false);
	//이전 프레임 유지
	//std::fill(heldKeys.begin(), heldKeys.end(), false);
}
void InputMgr::UpdateEvent(const sf::Event& ev) 
{	
	//press, release
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
		heldKeys[ev.key.code] = false;
		downKeys[ev.key.code] = false;
		upKeys[ev.key.code] = true;
		break;
	}
}
void InputMgr::Update(float dt)
{
	for (auto& pair : axisInfoMap)
	{
		AxisInfo& axisInfo = pair.second;
		float targetValue = 0.f;

		bool positivePressed = false;
		for (int key : axisInfo.positives)
		{
			if (heldKeys[key])
			{
				positivePressed = true;
				break;
			}
		}

		bool negativePressed = false;
		for (int key : axisInfo.negatives)
		{
			if (heldKeys[key])
			{
				negativePressed = true;
				break;
			}
		}

		if (positivePressed && !negativePressed)
			targetValue = 1.f;
		else if (negativePressed && !positivePressed)
			targetValue = -1.f;
		else
			targetValue = 0.f;

		if (targetValue != axisInfo.value)
		{
			float direction = (targetValue > axisInfo.value) ? 1.f : -1.f;
			axisInfo.value += direction * axisInfo.sensi * dt;
			axisInfo.value = Utils::Clamp(axisInfo.value, -1.f, 1.f);

			if ((direction > 0 && axisInfo.value > targetValue) ||
				(direction < 0 && axisInfo.value < targetValue))
			{
				axisInfo.value = targetValue;
			}
		}
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

float InputMgr::GetAxis(Axis axis)
{
	auto it = axisInfoMap.find(axis);
	if (it == axisInfoMap.end())
	{
		return 0.f;
	}
	return it->second.value;
}
