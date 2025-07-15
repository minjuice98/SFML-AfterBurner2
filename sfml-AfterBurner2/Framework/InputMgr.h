#pragma once

//키 매핑은 내부에서 하고, 게임 로직은 방향만 신경쓰도록 축 적용
enum class Axis
{
	Horizontal,
	Vertical,
};

struct AxisInfo
{
	//축 (-1.0 ~ 1.0)
	Axis axis;
	std::vector<int> positives;
	std::vector<int> negatives;

	float sensi = 10.f; //감도
	float value = 0.f;
};

class InputMgr
{
protected:
	static std::vector<bool> heldKeys;
	static std::vector<bool> upKeys;
	static std::vector<bool> downKeys;

public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev); //이벤트
	//static void Update(float dt); //시간

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
};