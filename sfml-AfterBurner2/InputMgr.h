#pragma once
class InputMgr
{
private:
	static std::vector<bool> heldKeys;
	static std::vector<bool> upKeys;
	static std::vector<bool> downKeys;

public:
	static void Init();
	static void Clear();

	static void UpdateEvent(const sf::Event& ev);
	static void Update(float dt);

	static bool GetKeyDown(sf::Keyboard::Key key);
	static bool GetKeyUp(sf::Keyboard::Key key);
	static bool GetKey(sf::Keyboard::Key key);
};

